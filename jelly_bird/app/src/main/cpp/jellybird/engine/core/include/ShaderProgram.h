#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "BaseInclude.h"
#include "Shader.h"
#include "Resource.h"

class ShaderProgram : public Resource {
public:
    ShaderProgram(const std::shared_ptr<Shader> & vertexShader, const std::shared_ptr<Shader> & fragmentShader);
    virtual ~ShaderProgram();

    virtual void use() = 0;
    virtual void stopUsing() = 0;
    virtual unsigned int getProgram();
    virtual void setBool(const std::string & name, bool value) const = 0;
    virtual void setInt(const std::string & name, int value) const = 0;
    virtual void setUInt(const std::string & name, unsigned int value) const = 0;
    virtual void setFloat(const std::string & name, float value) const = 0;
    virtual void setVec2(const std::string & name, const glm::vec2 & value) const = 0;
    virtual void setVec2(const std::string & name, float x, float y) const = 0;
    virtual void setVec3(const std::string & name, const glm::vec3 & value) const = 0;
    virtual void setVec3(const std::string & name, float x, float y, float z) const = 0;
    virtual void setVec4(const std::string & name, const glm::vec4 & value) const = 0;
    virtual void setVec4(const std::string & name, float x, float y, float z, float w) const = 0;
    virtual void setMat2(const std::string & name, const glm::mat2 & mat) const = 0;
    virtual void setMat3(const std::string & name, const glm::mat3 & mat) const = 0;
    virtual void setMat4(const std::string & name, const glm::mat4 & mat) const = 0;
protected:
    std::shared_ptr<Shader> vertexShader;
    std::shared_ptr<Shader> fragmentShader;
    unsigned int shaderProgram;
};

#endif