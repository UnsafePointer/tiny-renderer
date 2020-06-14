#include "Renderer.hpp"
#include <iostream>
#include "Framebuffer.hpp"
#include "RendererDebugger.hpp"

using namespace std;

Renderer::Renderer(uint32_t width, uint32_t height, uint32_t scale) : width(width), height(height), scale(scale) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * scale, height * scale, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        cout << "Failed to initialize the OpenGL context." << endl;
        exit(1);
    }
    cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << endl;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    program = make_unique<RendererProgram>("glsl/vertex.glsl", "glsl/fragment.glsl");
    program->useProgram();

    GLuint offsetUniform = program->findProgramUniform("offset");
    glUniform2f(offsetUniform, 0.0, 0.0);

    buffer = make_unique<RendererBuffer<Vertex>>(program, 1024);

    framebufferTexture = make_unique<Texture>(width * scale, height * scale);

    checkForOpenGLErrors();
}

Renderer::~Renderer() {
    SDL_Quit();
}

void Renderer::addVertices(std::vector<Vertex> vertices) {
    buffer->addData(vertices);
}

void Renderer::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    buffer->draw();
    SDL_GL_SwapWindow(window);
    checkForOpenGLErrors();
}
