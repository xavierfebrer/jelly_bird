#ifndef TEXTURE2DSHADER_H
#define TEXTURE2DSHADER_H

#include "ShaderProgram.h"
#include "Color.h"

class Texture2DShader : virtual public ShaderProgram {
public:
    Texture2DShader(const std::shared_ptr<Shader> & vertexShader, const std::shared_ptr<Shader> & fragmentShader);
    virtual ~Texture2DShader() override;

    virtual void setMVP(const glm::mat4 & mvp) = 0;
    virtual void setOffset(const glm::vec2 & offset) = 0;
    virtual void setScale(const glm::vec2 & scale) = 0;
    virtual void setTint(const Color & tint) = 0;
    virtual void setFlip(bool flipX, bool flipY) = 0;
};

#endif