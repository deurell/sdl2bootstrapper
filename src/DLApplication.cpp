//
// Created by Mikael Deurell on 2017-07-16.
//

#include "DLApplication.h"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL2/SDL_image.h>
#include <iostream>

void DLApplication::Run() {
    InitScreen("OpenGL 3.2");

    SDL_Event event{};
    bool quit = false;
    while (!quit) {
        SDL_GetTicks();
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) { quit = true; }
        }
        Render();
    }
    CleanUp();
}

void DLApplication::SdlDie(std::string const &message) const {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}

void DLApplication::InitScreen(std::string const &title) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SdlDie("Failed to init SDL Video");
    }

    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    int imgFlags = IMG_INIT_PNG;
    if (IMG_Init(imgFlags) == 0) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    constexpr int screenWidth = 960;
    constexpr int screen_height = 540;

    mWindow = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            screenWidth, screen_height, SDL_WINDOW_OPENGL
    );

    if (mWindow == nullptr) {
        SdlDie("Couldn't create window");
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr) {
        SdlDie("Couldn't create renderer");
    }
    SDL_RenderSetLogicalSize(mRenderer, screenWidth, screen_height);
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

    mSurface = IMG_Load("image.png");
    mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);

    mMainContext = SDL_GL_CreateContext(mWindow);
    if (mMainContext == nullptr) {
        SdlDie("Failed to create OpenGL context");
    }

    // Get OpenGL props
    printf("OpenGL loaded\n");

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    // Use v-sync
    SDL_GL_SetSwapInterval(1);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int height;
    int width;
    SDL_GetWindowSize(mWindow, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void DLApplication::Render() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_Rect rect {150, 150, 200, 100};
    SDL_RenderDrawRect(mRenderer, &rect);

    SDL_Rect dstRect {0, 0, 200, 200};
    SDL_Rect srcRect {150, 150, 200, 200};
    SDL_RenderCopy(mRenderer, mTexture, &srcRect, &dstRect );
    SDL_RenderPresent(mRenderer);
}

void DLApplication::CleanUp() {
    SDL_FreeSurface(mSurface);
    IMG_Quit();
}
