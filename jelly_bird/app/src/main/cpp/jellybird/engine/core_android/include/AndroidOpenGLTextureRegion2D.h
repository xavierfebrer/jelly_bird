#ifndef ANDROID_OPEN_GL_TEXTURE_REGION_2D_H
#define ANDROID_OPEN_GL_TEXTURE_REGION_2D_H

#include "../../core/include/TextureRegion2D.h"
#include "AndroidOpenGLTexture2D.h"
#include <GLES3/gl32.h>
#include <android_native_app_glue.h>

class AndroidOpenGLTextureRegion2D : public TextureRegion2D {
public:
    android_app* app;

    AndroidOpenGLTextureRegion2D(android_app* app, AndroidOpenGLTexture2D * texture2D, int x, int y, int w, int h);
    AndroidOpenGLTextureRegion2D(android_app* app, AndroidOpenGLTexture2D * texture2D, const Rect<int> & region);
    virtual ~AndroidOpenGLTextureRegion2D();

    virtual bool load() override;
    virtual bool unLoad() override;
};

#endif