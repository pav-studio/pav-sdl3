#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "lib/texture/texture_region.h"
#include "lib/rect/rect.h"

class Sprite {
private:
    std::vector<TextureRegion> frames;

    int currentFrame = 0;
    float frameTime = 0.1f;
    float timer = 0.0f;

public:

    float x = 0;
    float y = 0;

    float width = 0;
    float height = 0;

    float originX = 0;
    float originY = 0;

    float scaleX = 1.0f;
    float scaleY = 1.0f;

    float opacity = 1.0f;

    float rotation = 0.0f;

    bool flipX = false;
    bool flipY = false;

    bool visible = true;

    Rect bounds;

    Sprite() = default;

    void setFrames(const std::vector<TextureRegion>& f) {
        frames = f;

        if (!frames.empty()) {
            width = frames[0].src.w;
            height = frames[0].src.h;

            bounds.w = width;
            bounds.h = height;
        }
    }

    void update(float dt) {
        if (frames.empty()) return;

        timer += dt;

        while (timer >= frameTime) {
            timer -= frameTime;
            currentFrame = (currentFrame + 1) % frames.size();
        }

        bounds.x = x;
        bounds.y = y;

        bounds.w = width * scaleX;
        bounds.h = height * scaleY;
    }

    void draw(SDL_Renderer* renderer) {
        if (!visible || frames.empty()) return;

        auto& frame = frames[currentFrame];

        SDL_FRect dst = {
            (float)(int)x,
            (float)(int)y,
            width * scaleX,
            height * scaleY
        };

        SDL_FPoint center = {
            originX,
            originY
        };

        SDL_FlipMode flip = SDL_FLIP_NONE;

        if (flipX && flipY)
            flip = (SDL_FlipMode)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        else if (flipX)
            flip = SDL_FLIP_HORIZONTAL;
        else if (flipY)
            flip = SDL_FLIP_VERTICAL;

        Uint8 alpha = (Uint8)(opacity * 255.0f);
        SDL_SetTextureAlphaMod(frame.texture, alpha);

        SDL_RenderTextureRotated(
            renderer,
            frame.texture,
            &frame.src,
            &dst,
            rotation,
            &center,
            flip
        );
    }

    Rect getBounds() const {
        return bounds;
    }
};