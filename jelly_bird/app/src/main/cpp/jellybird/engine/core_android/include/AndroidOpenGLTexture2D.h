#ifndef ANDROID_OPEN_GL_TEXTURE_2D_H
#define ANDROID_OPEN_GL_TEXTURE_2D_H

#include "../../core/include/Texture2D.h"
#include <GLES3/gl32.h>
#include <android_native_app_glue.h>

class AndroidOpenGLTexture2D : public Texture2D {
public:
    android_app* app;
    bool pathFromAssets;
    int nrChannels;
    unsigned char * data;
    unsigned int id;
    GLint location;

    AndroidOpenGLTexture2D(android_app* app, const std::string & path, bool pathFromAssets, GLint location, GLint tMinFilter = GL_NEAREST, GLint tMaxFilter = GL_NEAREST, GLint tWrapS = GL_REPEAT, GLint tWrapT = GL_REPEAT, GLint level = 0, GLenum type = GL_UNSIGNED_BYTE, bool flipOnLoad = false);
    virtual ~AndroidOpenGLTexture2D() override;

    virtual bool load() override;
    virtual bool unLoad() override;
    virtual void activeBind() override;
protected:
    GLint tWrapS, tWrapT;
    GLint tMinFilter, tMaxFilter;
    GLint level;
    GLenum type;
    bool flipOnLoad;
};

#endif