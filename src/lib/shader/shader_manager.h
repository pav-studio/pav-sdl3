#pragma once

#include "shader.h"

#include <unordered_map>
#include <string>

class ShaderManager {

private:

    std::unordered_map<
        std::string,
        Shader*
    > shaders;

public:

    void load(
        const std::string& name,
        const std::string& folder
    );

    Shader& get(
        const std::string& name
    );

    void clear();
};