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
    window = SDL_CreateWindow("しのぶ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * 6, height * 6, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        cout << "Failed to initialize the OpenGL context." << endl;
        exit(1);
    }
    cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << endl;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    screenTexture = make_unique<Texture>(width, height);
    screenProgram = make_unique<RendererProgram>("glsl/screen_vertex.glsl", "glsl/screen_fragment.glsl");
    screenBuffer = make_unique<RendererBuffer<Pixel>>(screenProgram, 1024);

    program = make_unique<RendererProgram>("glsl/vertex.glsl", "glsl/fragment.glsl");
    program->useProgram();
    GLuint widthUniform = program->findProgramUniform("width");
    glUniform1f(widthUniform, width);
    GLuint heightUniform = program->findProgramUniform("height");
    glUniform1f(heightUniform, height);

    buffer = make_unique<RendererBuffer<Vertex>>(program, width * height * 6);

    checkForOpenGLErrors();
}

Renderer::~Renderer() {
    SDL_Quit();
}

std::vector<Vertex> Renderer::verticesForPixel(Vertex pixel) {
    Vertex v1 = Vertex(pixel.position, pixel.color);
    Vertex v2 = Vertex({pixel.position.x + 1, pixel.position.y}, pixel.color);
    Vertex v3 = Vertex({pixel.position.x + 1, pixel.position.y + 1}, pixel.color);
    Vertex v4 = Vertex(pixel.position, pixel.color);
    Vertex v5 = Vertex({pixel.position.x, pixel.position.y + 1}, pixel.color);
    Vertex v6 = Vertex({pixel.position.x + 1, pixel.position.y + 1}, pixel.color);
    return {v1, v2, v3, v4, v5, v6};
}

void Renderer::addPixels(std::vector<Vertex> pixels) {
    std::vector<Vertex> vertices = {};
    for (const auto& pixel : pixels) {
        std::vector<Vertex> verticesForPixel = this->verticesForPixel(pixel);
        vertices.insert(vertices.end(), verticesForPixel.begin(), verticesForPixel.end());
    }
    buffer->addData(vertices);
}

void Renderer::render() {
    {
        glViewport(0, 0, 144, 160);
        Framebuffer framebuffer = Framebuffer(screenTexture);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        program->useProgram();
        buffer->draw(GL_TRIANGLES);
    }
    checkForOpenGLErrors();

    glViewport(0, 0, 160 * 6, 144 * 6);
    screenTexture->bind(GL_TEXTURE0);
    screenProgram->useProgram();
    std::vector<Pixel> data = {
        Pixel({-1.0f, -1.0f}, {0.0f, 1.0f}),
        Pixel({1.0f, -1.0f}, {1.0f, 1.0f}),
        Pixel({-1.0f, 1.0f}, {0.0f, 0.0f}),
        Pixel({1.0f, 1.0f}, {1.0f, 0.0f}),
    };
    screenBuffer->addData(data);
    screenBuffer->draw(GL_TRIANGLE_STRIP);

    SDL_GL_SwapWindow(window);
}

void Renderer::updateWindowTitle(std::string title) const {
    SDL_SetWindowTitle(window, title.c_str());
}
