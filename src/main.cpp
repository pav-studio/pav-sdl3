#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "lib/asset_manager/asset_manager.h"
#include "lib/texture/texture_region.h"

inline void draw(SDL_Renderer* r, TextureRegion& reg, float x, float y) {
    reg.dst.x = x;
    reg.dst.y = y;
    SDL_RenderTexture(r, reg.texture, &reg.src, &reg.dst);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Rogue Pong", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    AssetManager assets;

    assets.loadRegions(renderer, "bg", "assets/sprites/ui/bg.png", 32, 32);

    auto& tiles = assets.getRegions("bg");

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }

        SDL_RenderClear(renderer);

        if (!tiles.empty()) {
            draw(renderer, tiles[0], 200, 200);
        }

        SDL_RenderPresent(renderer);
    }

    assets.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}