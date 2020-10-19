#ifndef ANDROID_OPEN_GL_SHADER_PROGRAM_H
#define ANDROID_OPEN_GL_SHADER_PROGRAM_H

#include "../../core/include/ShaderProgram.h"
#include "AndroidOpenGLShader.h"

class AndroidOpenGLShaderProgram : virtual public ShaderProgram {
public:
    AndroidOpenGLShaderProgram(const std::shared_ptr<AndroidOpenGLShader> & vertexShader, const std::shared_ptr<AndroidOpenGLShader> & fragmentShader);
    virtual ~AndroidOpenGLShaderProgram() override;

    virtual bool load() override;
    virtual bool unLoad() override;
    virtual void use() override;
    virtual void stopUsing() override;
    virtual void setBool(const std::string & name, bool value) const override;
    virtual void setInt(const std::string & name, int value) const override;
    virtual void setUInt(const std::string & name, unsigned int value) const override;
    virtual void setFloat(const std::string & name, float value) const override;
    virtual void setVec2(const std::string & name, const glm::vec2 & value) const override;
    virtual void setVec2(const std::string & name, float x, float y) const override;
    virtual void setVec3(const std::string & name, const glm::vec3 & value) const override;
    virtual void setVec3(const std::string & name, float x, float y, float z) const override;
    virtual void setVec4(const std::string & name, const glm::vec4 & value) const override;
    virtual void
    setVec4(const std::string & name, float x, float y, float z, float w) const override;
    virtual void setMat2(const std::string & name, const glm::mat2 & mat) const override;
    virtual void setMat3(const std::string & name, const glm::mat3 & mat) const override;
    virtual void setMat4(const std::string & name, const glm::mat4 & mat) const override;
};

#endif