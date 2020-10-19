#include "../../../include/AndroidOpenGLShaderProgram.h"

AndroidOpenGLShaderProgram::AndroidOpenGLShaderProgram(
        const std::shared_ptr<AndroidOpenGLShader> & vertexShader,
        const std::shared_ptr<AndroidOpenGLShader> & fragmentShader) : ShaderProgram(vertexShader,
                                                                                     fragmentShader) {
}

AndroidOpenGLShaderProgram::~AndroidOpenGLShaderProgram() {
    unLoad();
}

bool AndroidOpenGLShaderProgram::load() {
    if(!loaded) {
        if(vertexShader->load() && fragmentShader->load()) {
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader->getShader());
            glAttachShader(shaderProgram, fragmentShader->getShader());
            glLinkProgram(shaderProgram);
            GLint linkOK = GL_FALSE;
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkOK);
            vertexShader->deleteShader();
            fragmentShader->deleteShader();
            if(linkOK != GL_TRUE) {
                GLint logLength = 0;
                glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
                std::vector<char> logContainer(logLength);
                glGetProgramInfoLog(shaderProgram, logLength, NULL, logContainer.data());
                std::string information(begin(logContainer), end(logContainer));
                std::cerr << "*** Link program: " << information << std::endl;
                loaded = unLoad();
            } else {
                loaded = true;
            }
        } else {
            loaded = unLoad();
        }
    }
    return loaded;
}

bool AndroidOpenGLShaderProgram::unLoad() {
    if(loaded) {
        loaded = vertexShader->unLoad() ? loaded : false;
        loaded = fragmentShader->unLoad() ? loaded : false;
        glDeleteProgram(shaderProgram);
        loaded = false;
    }
    return !loaded;
}

void AndroidOpenGLShaderProgram::use() {
    glUseProgram(shaderProgram);
}

void AndroidOpenGLShaderProgram::stopUsing() {
    glUseProgram(0);
}

void AndroidOpenGLShaderProgram::setBool(const std::string & name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int) value);
}

void AndroidOpenGLShaderProgram::setInt(const std::string & name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void AndroidOpenGLShaderProgram::setUInt(const std::string & name, unsigned int value) const {
    glUniform1ui(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void AndroidOpenGLShaderProgram::setFloat(const std::string & name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void AndroidOpenGLShaderProgram::setVec2(const std::string & name, const glm::vec2 & value) const {
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

void AndroidOpenGLShaderProgram::setVec2(const std::string & name, float x, float y) const {
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}

void AndroidOpenGLShaderProgram::setVec3(const std::string & name, const glm::vec3 & value) const {
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

void
AndroidOpenGLShaderProgram::setVec3(const std::string & name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}

void AndroidOpenGLShaderProgram::setVec4(const std::string & name, const glm::vec4 & value) const {
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

void AndroidOpenGLShaderProgram::setVec4(const std::string & name, float x, float y, float z,
                                         float w) const {
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
}

void AndroidOpenGLShaderProgram::setMat2(const std::string & name, const glm::mat2 & mat) const {
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void AndroidOpenGLShaderProgram::setMat3(const std::string & name, const glm::mat3 & mat) const {
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void AndroidOpenGLShaderProgram::setMat4(const std::string & name, const glm::mat4 & mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}