#pragma once
#include "lib/screen/screen.h"
#include "lib/asset_manager/asset_manager.h"
#include "lib/font_manager/font_manager.h"
#include "lib/sprite/sprite.h"
#include <iostream>

class GameScreen : public Screen {
private:
    AssetManager* assets;
    SDL_Renderer* renderer;
    std::vector<TextureRegion>* tiles;

    Sprite player;
    Sprite trigger;

    float speed = 200.0f;
    FontManager fonts;

public:
    GameScreen(AssetManager* assets, SDL_Renderer* renderer)
        : assets(assets), renderer(renderer) {
        }

    void onEnter() override {
        assets->loadRegions(renderer, "ui", "assets/sprites/ui/bg.png", 32, 32);

        tiles = &assets->getRegions("ui");

        std::vector<TextureRegion> playerFrames;
        for (int i = 0; i < 4 && i < (int)tiles->size(); i++) {
            playerFrames.push_back((*tiles)[i]);
        }

        std::vector<TextureRegion> triggerFrames;
        if (tiles->size() > 5) {
            triggerFrames.push_back((*tiles)[5]);
        }

        player.setFrames(playerFrames);
        player.setPosition(200, 200);
        player.setFrameTime(0.15f);

        trigger.setFrames(triggerFrames);
        trigger.setPosition(400, 200);
    }

    void update(float dt) override {
        const bool* keys = SDL_GetKeyboardState(NULL);

        float dx = 0, dy = 0;

        if (keys[SDL_SCANCODE_W]) dy -= 1;
        if (keys[SDL_SCANCODE_S]) dy += 1;
        if (keys[SDL_SCANCODE_A]) dx -= 1;
        if (keys[SDL_SCANCODE_D]) dx += 1;

        if (dx != 0 || dy != 0) {
            float len = SDL_sqrtf(dx*dx + dy*dy);
            dx /= len; dy /= len;
        }

        player.setPosition(
            player.getBounds().x + dx * speed * dt,
            player.getBounds().y + dy * speed * dt
        );

        player.update(dt);

        // 🔥 collision check
        if (player.getBounds().intersects(trigger.getBounds())) {
            std::cout << "HIT\n";
        }
    }

    void onKeyDown(SDL_Keycode key) override {
        if (key == SDLK_W) {
            // move up
            std::cout<< " W pressed" << "\n";
        }
    }

    void onMouseDown(int button, float x, float y) override {
        if (button == SDL_BUTTON_LEFT) {
            std::cout << "Clicked at: " << x << ", " << y << "\n";
        }
    }

    void render(SDL_Renderer* renderer) override {
        if (!tiles || tiles->empty()) return;

        auto& t = (*tiles)[0];

        SDL_FRect dst = t.dst;
        dst.x = 200;
        dst.y = 200;

        // SDL_RenderTexture(renderer, t.texture, &t.src, &dst);
        // fonts.draw(renderer, "default", "Hello SDL3", 100, 100);
        player.draw(renderer);
        trigger.draw(renderer);

    }
};