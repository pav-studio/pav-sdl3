#pragma once
#include "lib/screen/screen.h"

class ScreenManager {
private:
    Screen* current = nullptr;

public:
    void setScreen(Screen* screen) {
        if (current) current->onExit();
        current = screen;
        if (current) current->onEnter();
    }

    void update(float dt) {
        if (current) current->update(dt);
    }

    void render(SDL_Renderer* renderer) {
        if (current) current->render(renderer);
    }

    void handleEvent(const SDL_Event& e) {
        if (!current) return;

        switch (e.type) {

        case SDL_EVENT_KEY_DOWN:
            current->onKeyDown(e.key.key);
            break;

        case SDL_EVENT_KEY_UP:
            current->onKeyUp(e.key.key);
            break;

        case SDL_EVENT_MOUSE_MOTION:
            current->onMouseMove(e.motion.x, e.motion.y);
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            current->onMouseDown(e.button.button, e.button.x, e.button.y);
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            current->onMouseUp(e.button.button, e.button.x, e.button.y);
            break;
        }
    }
};