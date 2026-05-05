#pragma once

struct Rect {
    float x, y, w, h;

    Rect() = default;

    Rect(float x, float y, float w, float h)
        : x(x), y(y), w(w), h(h) {}

    bool intersects(const Rect& other) const {
        return !(x + w < other.x ||
                 x > other.x + other.w ||
                 y + h < other.y ||
                 y > other.y + other.h);
    }

    bool contains(float px, float py) const {
        return (px >= x && px <= x + w &&
                py >= y && py <= y + h);
    }
};