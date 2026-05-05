#include "font_manager.h"
#include <iostream>


bool FontManager::load(const std::string& name,
                       const std::string& path,
                       int size) {

    if (fonts.find(name) != fonts.end()) return true;

    TTF_Font* font = TTF_OpenFont(path.c_str(), size);

    if (!font) {
        std::cout << "Failed to load font: " << path 
          << " Error: " << SDL_GetError() << "\n";
        return false;
    }

    fonts[name] = font;
    return true;
}

TTF_Font* FontManager::get(const std::string& name) {
    auto it = fonts.find(name);
    if (it == fonts.end()) {
        std::cout << "Font not found: " << name << "\n" << " Error: " << SDL_GetError() << "\n";;
        return nullptr;
    }
    return it->second;
}

void FontManager::draw(SDL_Renderer* renderer,
                       const std::string& fontName,
                       const std::string& text,
                       float x, float y,
                       SDL_Color color) {

    std::string key = fontName + "|" + text;

    if (cache.find(key) == cache.end()) {
        TTF_Font* font = get(fontName);
        if (!font) return;

        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        cache[key] = {texture, surface->w, surface->h};
        SDL_DestroySurface(surface);
    }

    auto& t = cache[key];

    SDL_FRect dst = {x, y, (float)t.w, (float)t.h};
    SDL_RenderTexture(renderer, t.texture, NULL, &dst);
}

void FontManager::clear() {
    for (auto& pair : fonts) {
        TTF_CloseFont(pair.second);
    }
    fonts.clear();
}