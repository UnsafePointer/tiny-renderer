#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "RendererProgram.hpp"
#include "RendererBuffer.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"

class Renderer {
    SDL_GLContext glContext;
    SDL_Window *window;

    uint32_t width;
    uint32_t height;
    uint32_t scale;

    std::unique_ptr<RendererProgram> program;
    std::unique_ptr<RendererBuffer<Vertex>> buffer;

    std::unique_ptr<Texture> framebufferTexture;

    std::unique_ptr<RendererProgram> screenProgram;

    std::vector<Vertex> verticesForPixel(Vertex pixel);
public:
    Renderer(uint32_t width, uint32_t height, uint32_t scale);
    ~Renderer();

    void render();

    void addPixels(std::vector<Vertex> pixels);
};
