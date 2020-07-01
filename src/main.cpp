#include "Renderer.hpp"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    std::vector<Vertex> pixels = {
        Vertex(0, 0,  255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f),
        Vertex(0, 1,  170.0f / 255.0f, 170.0f / 255.0f, 170.0f / 255.0f),
        Vertex(1, 0,  85.0f / 255.0f, 85.0f / 255.0f, 85.0f / 255.0f),
        Vertex(1, 1,  0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f),
    };

    Renderer renderer = Renderer(2, 2, 300);
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        renderer.addPixels(pixels);
        renderer.render();
    }
    SDL_Quit();
    return 0;
}
