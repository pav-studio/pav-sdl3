#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "lib/texture/texture_region.h"

class AssetManager {
    private:
        std::unordered_map<std::string, SDL_Texture*> textures;

    public:
        std::unordered_map<std::string, std::vector<TextureRegion>> regions;

        void loadRegions(SDL_Renderer* renderer,
                        const std::string& name,
                        const std::string& path,
                        int tileW, int tileH);

        std::vector<TextureRegion>& getRegions(const std::string& name);
        void loadTexture(SDL_Renderer* renderer,
                        const std::string& name,
                        const std::string& path);

        SDL_Texture* getTexture(const std::string& name);

        void clear();

    ~AssetManager() {
        clear();
    }
};