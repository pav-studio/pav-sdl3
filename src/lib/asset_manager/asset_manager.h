#pragma once

#include <glad/glad.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "lib/texture/texture_region.h"

class AssetManager {
    private:
        std::unordered_map<std::string, GLuint> textures;

    public:
        std::unordered_map<std::string, std::vector<TextureRegion>> regions;

        void loadRegions(const std::string& name,
                        const std::string& path,
                        int tileW, int tileH);

        std::vector<TextureRegion>& getRegions(const std::string& name);
        void loadTexture(const std::string& name,
                        const std::string& path);

        GLuint getTexture(const std::string& name);

        void clear();

    ~AssetManager() {
        clear();
    }
};