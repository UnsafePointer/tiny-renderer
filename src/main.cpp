#include "Renderer.hpp"

int main() {
    Renderer renderer = Renderer();
    std::vector<Vertex> vertices = {
         Vertex(-0.5f, -0.5f,  1.0f, 0.0f, 0.0f),
         Vertex(0.0f, 0.5f,  0.0f, 1.0f, 0.0f),
         Vertex(0.5f,  -0.5f,  0.0f, 0.0f, 1.0f)
    };
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        renderer.addPolygon(vertices);
        renderer.prepareFrame();
        renderer.render();
        renderer.finishFrame();
    }
    SDL_Quit();
    return 0;
}
