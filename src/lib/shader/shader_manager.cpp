#include "shader_manager.h"

void ShaderManager::load(
    const std::string& name,
    const std::string& folder
) {

    Shader* shader = new Shader();

    shader->load(
        folder + "/vert.glsl",
        folder + "/frag.glsl"
    );

    shaders[name] = shader;
}

Shader& ShaderManager::get(
    const std::string& name
) {

    return *shaders[name];
}

void ShaderManager::clear() {

    for (auto& pair : shaders) {

        delete pair.second;
    }

    shaders.clear();
}