#pragma once
#include <SDL3/SDL.h>

#pragma once

#include <SDL3/SDL.h>

class Screen {

public:

    virtual ~Screen() = default;

    virtual void onEnter() {}
    virtual void onExit() {}

    virtual void update(float dt) = 0;

    virtual void render() = 0;

    virtual void onKeyDown(SDL_Keycode key) {}
    virtual void onKeyUp(SDL_Keycode key) {}

    virtual void onMouseMove(float x, float y) {}

    virtual void onMouseDown(
        int button,
        float x,
        float y
    ) {}

    virtual void onMouseUp(
        int button,
        float x,
        float y
    ) {}
};