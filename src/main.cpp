#include <SDL3/SDL.h>
#include "screens/game_screen.h"
#include "lib/asset_manager/asset_manager.h"
#include "lib/screen_manager/screen_manager.h"
#include "lib/font_manager/font_manager.h"
#include "lib/camera/camera.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Rogue Pong", 1280/2, 720/2, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    Camera camera(1280/2, 720/2);

    AssetManager assets;
    ScreenManager manager;

    GameScreen game(&assets, renderer);
    manager.setScreen(&game);

    bool running = true;
    SDL_Event e;

    Uint64 last = SDL_GetTicks();

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_WINDOW_RESIZED) {
                int w = e.window.data1;
                int h = e.window.data2;
            }
            if (e.type == SDL_EVENT_QUIT)
                running = false;

            manager.handleEvent(e);
        }
        

        Uint64 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        manager.update(dt);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        camera.apply(renderer);
        manager.render(renderer);
        camera.reset(renderer);
        SDL_RenderPresent(renderer);
    }

    assets.clear();
    
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}