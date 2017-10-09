#include <cstdio>
#include <cstdlib>
#include "glad/glad.h"
#include "DLApplication.h"
#include <SDL2/SDL.h>

static const int SCREEN_WIDTH = 960;
static const int SCREEN_HEIGHT = 540;
static SDL_Window *window = nullptr;
static SDL_GLContext context;
static const int FRAMES_PER_SECOND = 60;

static void sdlDie(const char *message) {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdlDie("Failed to init SDL Video");
    }
    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetSwapInterval(1);

    window = SDL_CreateWindow(
            "Demo",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL
    );

    if (nullptr == window) {
        sdlDie("Couldn't create window");
    }

    context = SDL_GL_CreateContext(window);
    if (nullptr == context) {
        sdlDie("Failed to create OpenGL context");
    }

    printf("OpenGL loaded\n");
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    auto application = CreateApplication();
    application->Initialize(width, height);

    Uint32 lastTime = 0;
    SDL_Event event {};
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { quit = true; }
        }
        Uint32 currentTime = SDL_GetTicks();
        float delta = currentTime - lastTime;
        lastTime = currentTime;

        application->UpdateAnimation(delta/1000);
        application->Render();

        if (delta < 1000 / FRAMES_PER_SECOND) {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - delta);
        }
        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
    return 0;
}