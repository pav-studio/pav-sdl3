#pragma once

#include <glad/glad.h>

struct TextureRegion {

    GLuint textureID = 0;

    float x = 0;
    float y = 0;

    float w = 0;
    float h = 0;

    float textureWidth = 1;
    float textureHeight = 1;

    TextureRegion() = default;

    TextureRegion(
        GLuint tex,
        float px,
        float py,
        float pw,
        float ph,
        float texW,
        float texH
    )
        : textureID(tex),
          x(px),
          y(py),
          w(pw),
          h(ph),
          textureWidth(texW),
          textureHeight(texH) {
    }
};