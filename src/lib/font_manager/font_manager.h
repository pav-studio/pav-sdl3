#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>
#include <string>

class FontManager {
    
    private:
        std::unordered_map<std::string, TTF_Font*> fonts;
        struct CachedText {
            SDL_Texture* texture;
            int w, h;
        };

        std::unordered_map<std::string, CachedText> cache;

    public:
        bool load(const std::string& name,
                const std::string& path,
                int size);

        TTF_Font* get(const std::string& name);

        void draw(SDL_Renderer* renderer,
                const std::string& fontName,
                const std::string& text,
                float x, float y,
                SDL_Color color = {255,255,255,255});

        void clear();

    ~FontManager() {
        clear();
    }
};