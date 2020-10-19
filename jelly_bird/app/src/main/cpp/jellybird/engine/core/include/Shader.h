#ifndef SHADER_H
#define SHADER_H

#include "BaseInclude.h"
#include "Util.h"

class Shader {
public:
    Shader(const std::string & path);
    virtual ~Shader();

    virtual bool load();
    virtual bool unLoad();
    virtual bool isLoaded();
    virtual void deleteShader() = 0;
    virtual long getShader() = 0;

    virtual std::string getShaderPath();
    virtual void setShaderPath(const std::string & path);
protected:
    std::string path;
    bool loaded;
    long shader;

    virtual std::string readShaderSource() = 0;
    virtual bool compileShader(const std::string & shaderSource) = 0;
};

#endif