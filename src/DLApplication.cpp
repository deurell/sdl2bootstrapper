//
// Created by mikae on 2017-07-16.
//

#include "DLApplication.h"
#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include <glad/glad.h>
#include <SDL2/SDL_image.h>

// static const int SCREEN_FULLSCREEN = 0;
constexpr int SCREEN_WIDTH = 960;
constexpr int SCREEN_HEIGHT = 540;

void DLApplication::run() {
    initScreen("OpenGL 3.2");

    Uint32 currentTime, lastTime;
    float deltaTime;

    SDL_Event event;
    bool quit = false;
    while (!quit) {

        lastTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;

        // process all events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { quit = true; }
        }

        // render
        render();
    }

}

void DLApplication::sdlDie(const char *message) {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}

void DLApplication::initScreen(const char *title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdlDie("Failed to init SDL Video");
    }

    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) && imgFlags)) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    mWindow = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL
    );

    if (nullptr == mWindow) {
        sdlDie("Couldn't create window");
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == mRenderer) {
        sdlDie("Couldn't create renderer");
    }

    SDL_RenderSetLogicalSize(mRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

    mMainContext = SDL_GL_CreateContext(mWindow);
    if (nullptr == mMainContext) {
        sdlDie("Failed to create OpenGL context");
    }

    // Get OpenGL props
    printf("OpenGL loaded\n");
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    // Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int width, height;
    SDL_GetWindowSize(mWindow, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void DLApplication::render() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 100;
    rect.h = 100;
    SDL_RenderDrawRect(mRenderer, &rect);
    SDL_RenderPresent(mRenderer);
}
