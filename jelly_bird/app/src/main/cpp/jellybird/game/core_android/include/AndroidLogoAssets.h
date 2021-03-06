#ifndef ANDROID_LOGO_ASSETS_H
#define ANDROID_LOGO_ASSETS_H

#include "../../core/include/LogoAssets.h"
#include <GLES3/gl32.h>
#include <android_native_app_glue.h>
#include "../../../engine/core_android/include/AndroidOpenGLQuadTexture2D.h"
#include "../../../engine/core_android/include/AndroidOpenGLQuadTextureRegion2D.h"
#include "../../../engine/core_android/include/AndroidOpenGLTexture2DShader.h"
#include "../../../engine/core_android/include/AndroidOpenGLShader.h"
#include "../../../engine/core_android/include/AndroidOpenSLESSound.h"
#include "../../../engine/core_android/include/AndroidOpenSLESMusic.h"

class AndroidLogoAssets : public LogoAssets {
public:
    android_app* app;

    AndroidLogoAssets(android_app* app);
    virtual ~AndroidLogoAssets() override;

    virtual bool load() override;
    virtual bool unLoad() override;
};

#endif