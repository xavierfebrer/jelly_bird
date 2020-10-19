#include "../../../include/Shader.h"

Shader::Shader(const std::string & path) : path(path), loaded(false) {
}

Shader::~Shader() {
}

bool Shader::load() {
    if(!loaded && compileShader(readShaderSource())) {
        loaded = true;
    }
    return loaded;
}

bool Shader::unLoad() {
    if(loaded) {
        deleteShader();
        loaded = false;
    }
    return !loaded;
}

bool Shader::isLoaded() {
    return loaded;
}

std::string Shader::getShaderPath() {
    return path;
}

void Shader::setShaderPath(const std::string & path) {
    this->path = path;
}
