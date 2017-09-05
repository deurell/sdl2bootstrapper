//
// Created by Mikael Deurell on 2017-07-16.
//

#pragma once

#include <SDL2/SDL_video.h>
#include <SDL_render.h>
#include <string>

class SDL_Window;
class SDL_Renderer;

class DLApplication {

public:
    DLApplication() = default;
    ~DLApplication() = default;
    DLApplication(const DLApplication &rhs) = delete;
    DLApplication& operator=(const DLApplication &rhs) = delete;

    void Run();

private:
    void SdlDie(std::string const &message) const;
    void InitScreen(std::string const &title);
    void Render();
    void CleanUp();

    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
    SDL_GLContext mMainContext = nullptr;

    SDL_Surface *mSurface = nullptr;
    SDL_Texture *mTexture = nullptr;

};
