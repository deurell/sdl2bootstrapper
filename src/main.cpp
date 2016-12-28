#include <cstdio>
#include <cstdlib>
#include <SDL2/SDL.h>
#include "glad/glad.h"

// static const int SCREEN_FULLSCREEN = 0;
static const int SCREEN_WIDTH = 960;
static const int SCREEN_HEIGHT = 540;
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;
static SDL_GLContext mainContext;

static void sdlDie(const char *message) {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}

void initScreen(const char *title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdlDie("Failed to init SDL Video");
    }
    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL
    );

    if (nullptr == window) {
        sdlDie("Couldn't create window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == renderer) {
        sdlDie("Couldn't create renderer");
    }

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    mainContext = SDL_GL_CreateContext(window);
    if (nullptr == mainContext) {
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
    SDL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 100;
    rect.h = 100;
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) {
    initScreen("OpenGL 3.2");

    Uint32 currentTime, lastTime;
    float deltaTime;

    SDL_Event event;
    bool quit = false;
    while (!quit) {

        lastTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { quit = true; }
        }

        render();
    }
}