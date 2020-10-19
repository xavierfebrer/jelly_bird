#ifndef ANDROID_OPEN_GL_SHADER_H
#define ANDROID_OPEN_GL_SHADER_H

#include "../../core/include/Shader.h"
#include <GLES3/gl32.h>
#include <android_native_app_glue.h>

class AndroidOpenGLShader : public Shader {
public:
    android_app* app;
    bool pathFromAssets;

    AndroidOpenGLShader(android_app* app, const std::string & path, bool pathFromAssets, GLenum shaderType);
    virtual ~AndroidOpenGLShader() override;

    virtual void deleteShader() override;
    virtual long getShader() override;
protected:
    GLenum shaderType;

    virtual std::string readShaderSource() override;
    virtual bool compileShader(const std::string & shaderSource) override;
};

#endif