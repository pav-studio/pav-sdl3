#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

static std::string readFile(
    const std::string& path
) {

    std::ifstream file(path);

    if (!file.is_open()) {

        std::cout
            << "Failed to open shader: "
            << path
            << "\n";

        return "";
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

static GLuint compileShader(
    GLenum type,
    const std::string& source
) {

    GLuint shader =
        glCreateShader(type);

    const char* src =
        source.c_str();

    glShaderSource(
        shader,
        1,
        &src,
        NULL
    );

    glCompileShader(shader);

    int success;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success) {

        char info[512];

        glGetShaderInfoLog(
            shader,
            512,
            NULL,
            info
        );

        std::cout
            << "Shader Compile Error:\n"
            << info
            << "\n";
    }

    return shader;
}

bool Shader::load(
    const std::string& vertPath,
    const std::string& fragPath
) {

    std::string vertSource =
        readFile(vertPath);

    std::string fragSource =
        readFile(fragPath);

    GLuint vertexShader =
        compileShader(
            GL_VERTEX_SHADER,
            vertSource
        );

    GLuint fragmentShader =
        compileShader(
            GL_FRAGMENT_SHADER,
            fragSource
        );

    programID = glCreateProgram();

    glAttachShader(
        programID,
        vertexShader
    );

    glAttachShader(
        programID,
        fragmentShader
    );

    glLinkProgram(programID);

    int success;

    glGetProgramiv(
        programID,
        GL_LINK_STATUS,
        &success
    );

    if (!success) {

        char info[512];

        glGetProgramInfoLog(
            programID,
            512,
            NULL,
            info
        );

        std::cout
            << "Shader Link Error:\n"
            << info
            << "\n";

        return false;
    }

    glDeleteShader(vertexShader);

    glDeleteShader(fragmentShader);

    return true;
}

void Shader::use() {
    // std::cout << "USING SHADER: "
    //         << programID
    //         << "\n";
    glUseProgram(programID);
}

GLuint Shader::getID() const {

    return programID;
}

void Shader::setFloat(
    const std::string& name,
    float value
) {

    use();

    glUniform1f(
        glGetUniformLocation(
            programID,
            name.c_str()
        ),
        value
    );
}

Shader::~Shader() {

    if (programID != 0) {

        glDeleteProgram(programID);
    }
}