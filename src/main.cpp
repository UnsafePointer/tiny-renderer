#include "Renderer.hpp"

int main() {
    std::vector<uint8_t> tileData = { 0xFF, 0x00, 0x7E, 0xFF, 0x85, 0x81, 0x89, 0x83,
                                      0x93, 0x85, 0xA5, 0x8B, 0xC9, 0x97, 0x7E, 0xFF, };
    std::vector<uint8_t> VRAM = {};
    for (int i = 0; i < 384; i++) {
        VRAM.insert(VRAM.end(), tileData.begin(), tileData.end());
    }

    std::vector<Vertex> vertices = {
         Vertex(-0.5f, -0.5f,  1.0f, 0.0f, 0.0f),
         Vertex(0.0f, 0.5f,  0.0f, 1.0f, 0.0f),
         Vertex(0.5f,  -0.5f,  0.0f, 0.0f, 1.0f)
    };

    Renderer renderer = Renderer(2, 2, 100);
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        renderer.addVertices(vertices);
        renderer.render();
    }
    SDL_Quit();
    return 0;
}
