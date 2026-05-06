// renderer2d.h

#pragma once

#include <glad/glad.h>

#include "lib/texture/texture_region.h"
#include "lib/shader/shader.h"

class Renderer2D {

private:

    static Shader defaultShader;

    static Shader* currentShader;

    static float virtualWidth;
    static float virtualHeight;

    static GLuint VAO;
    static GLuint VBO;
    static GLuint EBO;

public:

    static void init();

    static void shutdown();

    static void setShader(
        Shader& shader
    );

    static void resetShader();

    static void setVirtualSize(float w, float h);

    static void draw(
        const TextureRegion& region,
        float x,
        float y,
        float width,
        float height
    );
};