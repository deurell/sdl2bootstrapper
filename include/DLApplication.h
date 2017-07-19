//
// Created by mikae on 2017-07-16.
//

#ifndef SDL2_GLAD_DLAPPLICATION_H
#define SDL2_GLAD_DLAPPLICATION_H

#include <SDL2/SDL_video.h>

class SDL_Window;
class SDL_Renderer;

class DLApplication {

public:
    DLApplication() = default;
    ~DLApplication() = default;
    DLApplication(const DLApplication&) = delete;

    void run();

private:
    void sdlDie(const char *message);
    void initScreen(const char* title);
    void render();

    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
    SDL_GLContext mMainContext = nullptr;
};

#endif //SDL2_GLAD_DLAPPLICATION_H