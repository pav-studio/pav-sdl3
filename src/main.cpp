#include <SDL3/SDL.h>
#include "screens/game_screen.h"
#include "lib/asset_manager/asset_manager.h"
#include "lib/screen_manager/screen_manager.h"
#include "lib/font_manager/font_manager.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Rogue Pong", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);


    AssetManager assets;
    ScreenManager manager;

    GameScreen game(&assets, renderer);
    manager.setScreen(&game);

    bool running = true;
    SDL_Event e;

    Uint64 last = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
                
            manager.handleEvent(e);
        }
        

        Uint64 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        manager.update(dt);

        SDL_RenderClear(renderer);
        manager.render(renderer);
        SDL_RenderPresent(renderer);
    }

    assets.clear();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}