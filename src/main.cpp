#include "Renderer.hpp"
#include <ctime>

std::vector<Vertex> generatePixels(int width, int height) {
    std::vector<Vertex> pixels = {};
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            pixels.push_back(Vertex(i, j,  rand() % 255 / 255.0f, rand() % 255 / 255.0f, rand() % 255 / 255.0f));
        }
    }
    return pixels;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    srand(time(NULL));
    int width = 160;
    int height = 144;

    Renderer renderer = Renderer(width, height);
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
        std::vector<Vertex> pixels = generatePixels(width, height);
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
