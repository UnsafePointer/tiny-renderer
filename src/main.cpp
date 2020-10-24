#include "Renderer.hpp"
#include <ctime>

std::vector<GLfloat> generateTextureData(int width, int height) {
    (void)width;
    (void)height;
    std::vector<GLfloat> data = {};
    // for (int i = 0; i < width; i++) {
    //     for (int j = 0; j < height; j++) {
    //         data.push_back(0x0);
    //         data.push_back(0xFF);
    //         data.push_back(0x0);
    //         data.push_back(0xFF);
    //     }
    // }

    data.push_back(0.0f);
    data.push_back(0.0f);
    data.push_back(0.0f);

    data.push_back(1.0f);
    data.push_back(1.0f);
    data.push_back(1.0f);

    data.push_back(0.0f);
    data.push_back(0.0f);
    data.push_back(0.0f);

    data.push_back(0.0f);
    data.push_back(0.0f);
    data.push_back(0.0f);
    return data;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    srand(time(NULL));
    int width = 600;
    int height = 400;

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
        std::vector<GLfloat> data = generateTextureData(width, height);
        renderer.addTextureData(data);
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
