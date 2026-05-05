#include "font.h"
#include <iostream>

bool Font::load(const std::string& path, int size) {
    font = TTF_OpenFont(path.c_str(), size);

    if (!font) {
        std::cout << "Failed to load font: " << path << "\n";
        return false;
    }

    return true;
}

void Font::draw(SDL_Renderer* renderer,
                const std::string& text,
                float x, float y,
                SDL_Color color) {

    if (!font) return;

    // 🔴 EXPENSIVE (we’ll optimize later)
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);

    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FRect dst;
    dst.x = x;
    dst.y = y;
    dst.w = surface->w;
    dst.h = surface->h;

    SDL_DestroySurface(surface);

    SDL_RenderTexture(renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
}

void Font::destroy() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}