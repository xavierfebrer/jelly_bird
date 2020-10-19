#include "..\..\..\include\ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::shared_ptr<Shader> & vertexShader, const std::shared_ptr<Shader> & fragmentShader)
        : vertexShader(vertexShader), fragmentShader(fragmentShader) {
}

ShaderProgram::~ShaderProgram() {
}

unsigned int ShaderProgram::getProgram() {
    return shaderProgram;
}
