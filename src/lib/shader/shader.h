#pragma once

#include <glad/glad.h>

#include <string>

class Shader {

    private:

        GLuint programID = 0;

    public:

        Shader() = default;

        Shader(const Shader&) = delete;

        Shader& operator=(
            const Shader&
        ) = delete;

        bool load(
            const std::string& vertPath,
            const std::string& fragPath
        );

        void use();

        GLuint getID() const;

        void setFloat(
            const std::string& name,
            float value
        );

        ~Shader();
};