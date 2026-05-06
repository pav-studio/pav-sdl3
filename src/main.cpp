#include <glad/glad.h>
#include <SDL3/SDL.h>
#include "screens/game_screen.h"
#include "lib/asset_manager/asset_manager.h"
#include "lib/screen_manager/screen_manager.h"
#include "lib/font_manager/font_manager.h"
#include "lib/camera/camera.h"
#include "lib/renderer/renderer2d.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    SDL_Window* window = SDL_CreateWindow(
        "Rogue Pong",
        720 / 2,
        1280 / 2,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (!glContext) {
        SDL_Log("OpenGL context failed: %s", SDL_GetError());
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_Log("Failed to initialize GLAD");
        return -1;
    }

    SDL_GL_SetSwapInterval(1);

    SDL_Log("OpenGL Version: %s", glGetString(GL_VERSION));

    Renderer2D::init();

    Renderer2D::setVirtualSize(
        720 / 2,
        1280 / 2
    );
    
    Camera camera(
        720 / 2,
        1280 / 2
    );

    AssetManager assets;
    ScreenManager manager;

    GameScreen game(&assets);
    manager.setScreen(&game);

    bool running = true;
    SDL_Event e;

    Uint64 last = SDL_GetTicks();

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_WINDOW_RESIZED) {
                w = e.window.data1;
                h = e.window.data2;
            }
            if (e.type == SDL_EVENT_QUIT)
                running = false;

            manager.handleEvent(e);
        }
        

        Uint64 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        manager.update(dt);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        camera.apply(w, h);
        manager.render();

        SDL_GL_SwapWindow(window);
    }

    assets.clear();
    Renderer2D::shutdown();
    TTF_Quit();
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}