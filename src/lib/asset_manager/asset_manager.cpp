#include "asset_manager.h"

#include <iostream>

void AssetManager::loadTexture(
    const std::string& name,
    const std::string& path
) {

    if (textures.find(name) != textures.end()) {
        return;
    }

    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface) {
        std::cout
            << "Failed to load: "
            << path
            << " Error: "
            << SDL_GetError()
            << "\n";

        return;
    }

    GLuint texture;

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_NEAREST
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_NEAREST
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP_TO_EDGE
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP_TO_EDGE
    );

    GLenum format =
        surface->format == SDL_PIXELFORMAT_RGBA32
        ? GL_RGBA
        : GL_RGB;

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        surface->w,
        surface->h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        surface->pixels
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    textures[name] = texture;

    SDL_DestroySurface(surface);
}

GLuint AssetManager::getTexture(
    const std::string& name
) {

    auto it = textures.find(name);

    if (it == textures.end()) {

        std::cout
            << "Texture not found: "
            << name
            << "\n";

        return 0;
    }

    return it->second;
}

void AssetManager::loadRegions(
    const std::string& name,
    const std::string& path,
    int tileW,
    int tileH
) {

    loadTexture(name, path);

    GLuint tex = getTexture(name);

    SDL_Surface* surface =
        IMG_Load(path.c_str());

    if (!surface) {
        return;
    }

    int w = surface->w;
    int h = surface->h;

    std::vector<TextureRegion> result;

    for (int y = 0; y < h; y += tileH) {

        for (int x = 0; x < w; x += tileW) {

            result.emplace_back(
                    tex,
                    x,
                    y,
                    tileW,
                    tileH,
                    w,
                    h
                );
        }
    }

    regions[name] = result;

    SDL_DestroySurface(surface);
}

std::vector<TextureRegion>&
AssetManager::getRegions(
    const std::string& name
) {
    return regions[name];
}

void AssetManager::clear() {

    regions.clear();

    for (auto& pair : textures) {

        glDeleteTextures(
            1,
            &pair.second
        );
    }

    textures.clear();
}