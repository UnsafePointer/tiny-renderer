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

    std::unique_ptr<Texture> texture;
    std::unique_ptr<RendererProgram> program;
    std::unique_ptr<RendererBuffer<Pixel>> buffer;
public:
    Renderer(uint32_t width, uint32_t height);
    ~Renderer();

    void render();

    void addTextureData(std::vector<GLfloat> textureData);

    void updateWindowTitle(std::string title) const;
};
