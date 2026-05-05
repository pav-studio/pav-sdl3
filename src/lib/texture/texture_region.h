#pragma once

#include <SDL3/SDL.h>

struct TextureRegion {
    SDL_Texture* texture;
    SDL_FRect src;  
    SDL_FRect dst;  

    TextureRegion(SDL_Texture* tex, float x, float y, float w, float h)
        : texture(tex) {
        src = {x, y, w, h};
        dst = {0, 0, w, h};
    }
};