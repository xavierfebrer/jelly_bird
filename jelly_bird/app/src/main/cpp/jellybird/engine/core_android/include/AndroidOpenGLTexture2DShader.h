#ifndef ANDROID_OPEN_GL_TEXTURE_2D_SHADER_H
#define ANDROID_OPEN_GL_TEXTURE_2D_SHADER_H

#include "../../../engine/core/include/Texture2DShader.h"
#include "AndroidOpenGLShader.h"
#include "AndroidOpenGLShaderProgram.h"

class AndroidOpenGLTexture2DShader : public AndroidOpenGLShaderProgram, public Texture2DShader {
public:
    AndroidOpenGLTexture2DShader(const std::shared_ptr<AndroidOpenGLShader> & vertexShader, const std::shared_ptr<AndroidOpenGLShader> & fragmentShader);
    virtual ~AndroidOpenGLTexture2DShader() override;

    virtual void setMVP(const glm::mat4 & mvp) override;
    virtual void setOffset(const glm::vec2 & offset) override;
    virtual void setScale(const glm::vec2 & scale) override;
    virtual void setTint(const Color & tint) override;
    virtual void setFlip(bool flipX, bool flipY) override;
};

#endif