#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Font {
private:
    TTF_Font* font = nullptr;

public:
    Font() = default;

    bool load(const std::string& path, int size);

    void draw(SDL_Renderer* renderer,
              const std::string& text,
              float x, float y,
              SDL_Color color = {255,255,255,255});

    void destroy();
};