#pragma once
#include "lib/screen/screen.h"
#include "lib/asset_manager/asset_manager.h"
#include "lib/font_manager/font_manager.h"

class GameScreen : public Screen {
private:
    AssetManager* assets;
    SDL_Renderer* renderer;
    std::vector<TextureRegion>* tiles;

    FontManager fonts;

public:
    GameScreen(AssetManager* assets, SDL_Renderer* renderer)
        : assets(assets), renderer(renderer) {
        }

    void onEnter() override {
        assets->loadRegions(renderer, "bg", "assets/sprites/ui/bg.png", 32, 32);
        fonts.load("default", "assets/fonts/default.ttf", 32);

        tiles = &assets->getRegions("bg");
    }

    void update(float dt) override {
        // game logic here
    }

    void render(SDL_Renderer* renderer) override {
        if (!tiles || tiles->empty()) return;

        auto& t = (*tiles)[0];

        SDL_FRect dst = t.dst;
        dst.x = 200;
        dst.y = 200;

        SDL_RenderTexture(renderer, t.texture, &t.src, &dst);
        fonts.draw(renderer, "default", "Hello SDL3", 100, 100);

    }
};