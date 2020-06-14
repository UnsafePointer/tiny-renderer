#include "Renderer.hpp"
#include <iostream>
#include "Framebuffer.hpp"
#include "RendererDebugger.hpp"

using namespace std;

const uint32_t WIDTH = 1024;
const uint32_t HEIGHT = 768;

Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
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

    framebufferTexture = make_unique<Texture>(WIDTH, HEIGHT);

    screenProgram = make_unique<RendererProgram>("glsl/screen_vertex.glsl", "glsl/screen_fragment.glsl");

    screenBuffer = make_unique<RendererBuffer<Pixel>>(screenProgram, 1024);
    checkForOpenGLErrors();
}

Renderer::~Renderer() {
    SDL_Quit();
}

void Renderer::addPolygon(std::vector<Vertex> vertices) {
    buffer->addData(vertices);
}

void Renderer::prepareFrame() {
    framebufferTexture->bind(GL_TEXTURE0);
    checkForOpenGLErrors();
}

void Renderer::render() {
    Framebuffer framebuffer = Framebuffer(framebufferTexture);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    buffer->draw();
    checkForOpenGLErrors();
}

void Renderer::finishFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    std::vector<Pixel> pixels = {
         Pixel({-1.0f, 1.0f}, {0.0f, 1.0f}),
         Pixel({-1.0f, -1.0f}, {0.0f, 0.0f}),
         Pixel({1.0f,  -1.0f}, {1.0f, 0.0f}),
         Pixel({-1.0f,  1.0f}, {0.0f, 1.0f}),
         Pixel({1.0f,  -1.0f}, {1.0f, 0.0f}),
         Pixel({1.0f,  1.0}, {1.0f, 1.0f})
    };
    screenBuffer->bind();
    screenProgram->useProgram();
    screenBuffer->addData(pixels);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture->object);
    screenBuffer->draw();
    SDL_GL_SwapWindow(window);
    checkForOpenGLErrors();
    return;
}
