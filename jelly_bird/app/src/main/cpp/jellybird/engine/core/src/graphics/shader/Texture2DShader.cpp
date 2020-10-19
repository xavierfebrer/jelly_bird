#include "../../../include/Texture2DShader.h"

Texture2DShader::Texture2DShader(const std::shared_ptr<Shader> & vertexShader, const std::shared_ptr<Shader> & fragmentShader)
        : ShaderProgram(vertexShader, fragmentShader) {
}

Texture2DShader::~Texture2DShader() {
}