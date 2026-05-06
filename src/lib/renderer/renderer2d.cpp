// renderer2d.cpp

#include "renderer2d.h"

#include <iostream>

Shader Renderer2D::defaultShader;

Shader* Renderer2D::currentShader = nullptr;

GLuint Renderer2D::VAO = 0;
GLuint Renderer2D::VBO = 0;
GLuint Renderer2D::EBO = 0;
float Renderer2D::virtualWidth = 1280.0f / 2.0f;
float Renderer2D::virtualHeight = 720.0f / 2.0f;

void Renderer2D::init() {


    

    defaultShader.load(
        "assets/shaders/default/vert.glsl",
        "assets/shaders/default/frag.glsl"
    );

    currentShader = &defaultShader;

    float vertices[] = {

        // positions      // UVs

         1.0f,  1.0f,     1.0f, 1.0f,
         1.0f, -1.0f,     1.0f, 0.0f,
        -1.0f, -1.0f,     0.0f, 0.0f,
        -1.0f,  1.0f,     0.0f, 1.0f
    };

    unsigned int indices[] = {

        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_DYNAMIC_DRAW
    );

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        EBO
    );

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)(2 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );
}

void Renderer2D::setVirtualSize(
    float w, float h
) {
    virtualWidth = w;
    virtualHeight = h;
}

void Renderer2D::setShader(
    Shader& shader
) {

    currentShader = &shader;
}

void Renderer2D::resetShader() {

    currentShader = &defaultShader;
}

void Renderer2D::draw(
    const TextureRegion& region,
    float x,
    float y,
    float width,
    float height
) {

    float screenW = virtualWidth;
    float screenH = virtualHeight;

    float left =
        (x / screenW) * 2.0f - 1.0f;

    float right =
        ((x + width) / screenW) * 2.0f - 1.0f;

    float top =
        1.0f - (y / screenH) * 2.0f;

    float bottom =
        1.0f - ((y + height) / screenH) * 2.0f;

    float u1 =
        region.x / region.textureWidth;

    float v1 =
        region.y / region.textureHeight;

    float u2 =
        (region.x + region.w)
        / region.textureWidth;

    float v2 =
        (region.y + region.h)
        / region.textureHeight;

    float vertices[] = {

        // positions      // UVs

        right, top,       u2, v1,
        right, bottom,    u2, v2,
        left,  bottom,    u1, v2,
        left,  top,       u1, v1
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    currentShader->use();

    glUniform1i(
        glGetUniformLocation(
            currentShader->getID(),
            "image"
        ),
        0
    );

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(
        GL_TEXTURE_2D,
        region.textureID
    );

    glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_INT,
        0
    );

    glBindVertexArray(0);
}

void Renderer2D::shutdown() {

    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);

    glDeleteBuffers(1, &EBO);
}