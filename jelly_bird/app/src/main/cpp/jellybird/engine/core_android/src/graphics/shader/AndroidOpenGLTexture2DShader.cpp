#include "../../../include/AndroidOpenGLTexture2DShader.h"

AndroidOpenGLTexture2DShader::AndroidOpenGLTexture2DShader(
        const std::shared_ptr<AndroidOpenGLShader> & vertexShader,
        const std::shared_ptr<AndroidOpenGLShader> & fragmentShader) : ShaderProgram(vertexShader,
                                                                                     fragmentShader),
                                                                       AndroidOpenGLShaderProgram(
                                                                               vertexShader,
                                                                               fragmentShader),
                                                                       Texture2DShader(vertexShader,
                                                                                       fragmentShader) {
}

AndroidOpenGLTexture2DShader::~AndroidOpenGLTexture2DShader() {
    unLoad();
}

void AndroidOpenGLTexture2DShader::setMVP(const glm::mat4 & mvp) {
    setMat4("mvp", mvp);
}

void AndroidOpenGLTexture2DShader::setOffset(const glm::vec2 & offset){
    setVec2("offset", offset);
}

void AndroidOpenGLTexture2DShader::setScale(const glm::vec2 & scale) {
    setVec2("scale", scale);
}

void AndroidOpenGLTexture2DShader::setTint(const Color & tint) {
    setVec4("tint", {tint.r, tint.g, tint.b, tint.a});
}

void AndroidOpenGLTexture2DShader::setFlip(bool flipX, bool flipY) {
    setBool("flipX", flipX);
    setBool("flipY", flipY);
}
