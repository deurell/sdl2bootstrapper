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
    void run();

private:
    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
    SDL_GLContext mMainContext;


    void sdlDie(const char *message);
    void initScreen(const char* title);
    void render();
};


#endif //SDL2_GLAD_DLAPPLICATION_H
