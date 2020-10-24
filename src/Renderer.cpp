#include "Renderer.hpp"
#include <iostream>
#include "Framebuffer.hpp"
#include "RendererDebugger.hpp"

using namespace std;

Renderer::Renderer(uint32_t width, uint32_t height) : width(width), height(height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    window = SDL_CreateWindow("しのぶ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        cout << "Failed to initialize the OpenGL context." << endl;
        exit(1);
    }
    cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << endl;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    texture = make_unique<Texture>(2, 2);
    program = make_unique<RendererProgram>("glsl/screen_vertex.glsl", "glsl/screen_fragment.glsl");
    program->useProgram();
    buffer = make_unique<RendererBuffer<Pixel>>(program, 4);

    checkForOpenGLErrors();
}

Renderer::~Renderer() {
    SDL_Quit();
}

void Renderer::addTextureData(std::vector<GLfloat> textureData) {
    texture->bind(GL_TEXTURE0);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_RGB,  GL_FLOAT, textureData.data());
    checkForOpenGLErrors();
}

void Renderer::render() {
    texture->bind(GL_TEXTURE0);
    program->useProgram();
    std::vector<Pixel> data = {
        Pixel({-1.0f, -1.0f}, {0.0f, 1.0f}),
        Pixel({1.0f, -1.0f}, {1.0f, 1.0f}),
        Pixel({-1.0f, 1.0f}, {0.0f, 0.0f}),
        Pixel({1.0f, 1.0f}, {1.0f, 0.0f}),
    };
    buffer->addData(data);
    buffer->draw(GL_TRIANGLE_STRIP);

    SDL_GL_SwapWindow(window);
}

void Renderer::updateWindowTitle(std::string title) const {
    SDL_SetWindowTitle(window, title.c_str());
}
