#pragma once

#include "lib/texture/texture_region.h"
#include "lib/rect/rect.h"
#include "lib/renderer/renderer2d.h"

class Sprite {

private:

    TextureRegion texture;

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

    void setTexture(
        const TextureRegion& region
    ) {

        texture = region;

        width = region.w;
        height = region.h;

        bounds.w = width;
        bounds.h = height;
    }

    void update(float dt) {

        bounds.x = x;
        bounds.y = y;

        bounds.w = width * scaleX;
        bounds.h = height * scaleY;
    }

    void setPosition(
        float px,
        float py
    ) {

        x = px;
        y = py;

        bounds.x = x;
        bounds.y = y;
    }

    void draw() {

        if (!visible)
            return;

        Renderer2D::draw(
            texture,

            x,
            y,

            width * scaleX,
            height * scaleY
        );
    }

    Rect getBounds() const {
        return bounds;
    }
};