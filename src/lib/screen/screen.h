#pragma once
#include <SDL3/SDL.h>

class Screen {
public:
    virtual ~Screen() = default;

    virtual void onEnter() {}
    virtual void onExit() {}

    virtual void update(float dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};