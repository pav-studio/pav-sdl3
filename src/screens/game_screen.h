#pragma once

#include "lib/screen/screen.h"
#include "lib/asset_manager/asset_manager.h"
#include "lib/font_manager/font_manager.h"
#include "lib/sprite/sprite.h"
#include "lib/renderer/renderer2d.h"
#include "lib/shader/shader_manager.h"
#include <iostream>

class GameScreen : public Screen {

private:
    float stateTime = 0.0f;
    AssetManager* assets;

    ShaderManager shaders;

    std::vector<TextureRegion>* tiles;

    Sprite player;
    Sprite trigger;

    float speed = 200.0f;

    FontManager fonts;

public:

    GameScreen(AssetManager* assets)
        : assets(assets) {
    }

    void onEnter() override {

        assets->loadRegions(
            "ui",
            "assets/sprites/ui/bg.png",
            32,
            32
        );

        tiles = &assets->getRegions("ui");

        shaders.load(
            "nebula",
            "assets/shaders/nebula"
        );

        if (tiles->size() > 0) {

            player.setTexture((*tiles)[0]);

            player.setPosition(200, 200);
        }

        if (tiles->size() > 5) {

            trigger.setTexture((*tiles)[5]);

            trigger.setPosition(400, 200);
        }
    }

    void update(float dt) override {
        stateTime += dt;
        const bool* keys =
            SDL_GetKeyboardState(NULL);

        float dx = 0;
        float dy = 0;

        if (keys[SDL_SCANCODE_W])
            dy -= 1;

        if (keys[SDL_SCANCODE_S])
            dy += 1;

        if (keys[SDL_SCANCODE_A])
            dx -= 1;

        if (keys[SDL_SCANCODE_D])
            dx += 1;

        if (dx != 0 || dy != 0) {

            float len =
                SDL_sqrtf(dx * dx + dy * dy);

            dx /= len;
            dy /= len;
        }

        player.setPosition(
            player.x + dx * speed * dt,
            player.y + dy * speed * dt
        );

        player.update(dt);

        trigger.update(dt);

        if (
            player.getBounds()
                .intersects(trigger.getBounds())
        ) {

            std::cout << "HIT\n";
        }
    }

    void onKeyDown(
        SDL_Keycode key
    ) override {

    }

    void onMouseDown(
        int button,
        float x,
        float y
    ) override {

        
    }

    void render() override {

        if (!tiles || tiles->empty())
            return;

        auto& background = (*tiles)[4];


        shaders.get("nebula")
            .setFloat(
                "uTime",
                stateTime
            );

        Renderer2D::setShader(
            shaders.get("nebula")
        );

        Renderer2D::draw(
            background,
            0,
            0,
            720 / 2,
            1280 / 2
        );

        Renderer2D::resetShader();

        player.draw();

        trigger.draw();
    }
};