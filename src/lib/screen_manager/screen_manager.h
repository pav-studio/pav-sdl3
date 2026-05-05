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
};