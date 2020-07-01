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
    uint32_t frameTimes = 0;
    uint32_t frameCounter = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        uint32_t frameTime = SDL_GetTicks();
        renderer.addPixels(pixels);
        renderer.render();
        frameTimes += SDL_GetTicks() - frameTime;
        frameCounter++;
        if (frameCounter >= 60) {
            frameCounter = 0;
            uint32_t averageFrameTime = frameTimes / 60;
            char buff[100];
            snprintf(buff, sizeof(buff), " - %d ms - %d ms", averageFrameTime, frameTimes);
            std::string buffAsStdStr = buff;
            renderer.updateWindowTitle(buffAsStdStr);
            frameTimes = 0;
        }
    }
    SDL_Quit();
    return 0;
}
