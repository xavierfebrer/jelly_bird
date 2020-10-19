#ifndef ANDROID_GAME_ASSETS_H
#define ANDROID_GAME_ASSETS_H

#include "../../core/include/GameAssets.h"
#include <GLES3/gl32.h>
#include <android_native_app_glue.h>
#include "../../../engine/core_android/include/AndroidOpenGLQuadTexture2D.h"
#include "../../../engine/core_android/include/AndroidOpenGLQuadTextureRegion2D.h"
#include "../../../engine/core_android/include/AndroidOpenGLTexture2DShader.h"
#include "../../../engine/core_android/include/AndroidOpenGLShader.h"
#include "../../../engine/core_android/include/AndroidOpenSLESSound.h"
#include "../../../engine/core_android/include/AndroidOpenSLESMusic.h"

class AndroidGameAssets : public GameAssets {
public:
    android_app* app;

    AndroidGameAssets(android_app* app);
    virtual ~AndroidGameAssets() override;

    virtual bool load() override;
    virtual bool unLoad() override;
protected:
    void createResources();
};

#endif