#pragma once
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
    Rect bounds;

    Sprite() = default;

    void setFrames(const std::vector<TextureRegion>& f) {
        frames = f;
        if (!frames.empty()) {
            bounds.w = frames[0].dst.w;
            bounds.h = frames[0].dst.h;
        }
    }

    void setPosition(float x, float y) {
        bounds.x = x;
        bounds.y = y;
    }

    void setFrameTime(float t) {
        frameTime = t;
    }

    void update(float dt) {
        if (frames.empty()) return;

        timer += dt;

        if (timer >= frameTime) {
            timer -= frameTime;
            currentFrame = (currentFrame + 1) % frames.size();
        }
    }

    void draw(SDL_Renderer* renderer) {
        if (frames.empty()) return;

        auto& frame = frames[currentFrame];

        SDL_FRect dst = {
            bounds.x,
            bounds.y,
            bounds.w,
            bounds.h
        };

        SDL_RenderTexture(renderer, frame.texture, &frame.src, &dst);
    }

    Rect getBounds() const {
        return bounds;
    }
};