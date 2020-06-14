#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "RendererProgram.hpp"
#include "RendererBuffer.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Pixel.hpp"

class Renderer {
    SDL_GLContext glContext;
    SDL_Window *window;

    std::unique_ptr<RendererProgram> program;
    std::unique_ptr<RendererBuffer<Vertex>> buffer;

    std::unique_ptr<Texture> framebufferTexture;

    std::unique_ptr<RendererProgram> screenProgram;
    std::unique_ptr<RendererBuffer<Pixel>> screenBuffer;
public:
    Renderer();
    ~Renderer();

    void prepareFrame();
    void render();
    void finishFrame();

    void addPolygon(std::vector<Vertex> vertices);
};
