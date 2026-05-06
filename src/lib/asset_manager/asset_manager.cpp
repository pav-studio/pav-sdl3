#include "asset_manager.h"
#include <iostream>

void AssetManager::loadTexture(SDL_Renderer* renderer,
                               const std::string& name,
                               const std::string& path) {

    if (textures.find(name) != textures.end()) {
        return;
    }

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cout << "Failed to load: " << path << " Error: " << SDL_GetError() << "\n";
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        std::cout << "Failed to create texture: " << path << "\n";
        return;
    }
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    textures[name] = texture;
}

SDL_Texture* AssetManager::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it == textures.end()) {
        std::cout << "Texture not found: " << name << "\n";
        return nullptr;
    }
    return it->second;
}


void AssetManager::loadRegions(SDL_Renderer* renderer,
                               const std::string& name,
                               const std::string& path,
                               int tileW, int tileH) {

    loadTexture(renderer, name, path);

    SDL_Texture* tex = getTexture(name);

    float w, h;
    SDL_GetTextureSize(tex, &w, &h);

    std::vector<TextureRegion> result;

    for (int y = 0; y < h; y += tileH) {
        for (int x = 0; x < w; x += tileW) {
            result.emplace_back(tex, x, y, tileW, tileH);
        }
    }

    regions[name] = result;
}

std::vector<TextureRegion>& AssetManager::getRegions(const std::string& name) {
    return regions[name];
}

void AssetManager::clear() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}