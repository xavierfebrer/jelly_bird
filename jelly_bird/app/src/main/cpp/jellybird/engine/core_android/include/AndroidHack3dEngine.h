#ifndef ANDROIDHACK3DENGINE_H
#define ANDROIDHACK3DENGINE_H

#include "../../core/include/Hack3dEngine.h"
#include "../../core_android/include/AndroidInput.h"
#include "AndroidOpenSLESAudio.h"
#include "../../core_android/include/AndroidGraphics.h"
#include "../../core_android/include/AndroidAssets.h"

class AndroidHack3dEngine : public Hack3dEngine {
public:
    android_app* app;

    static AndroidHack3dEngine & get();
    static void destroy();

    std::shared_ptr<AndroidInput> androidInput;
    std::shared_ptr<AndroidOpenSLESAudio> androidAudio;
    std::shared_ptr<AndroidGraphics> androidGraphics;
    std::shared_ptr<AndroidAssets> androidAssets;

    AndroidHack3dEngine();
    virtual ~AndroidHack3dEngine() override;

    virtual AndroidInput & input() override;
    virtual AndroidOpenSLESAudio & audio() override;
    virtual AndroidGraphics & graphics() override;
    virtual AndroidAssets & assets() override;

    virtual bool init() override;
    virtual bool isInitialized() override;
    virtual Hack3dEngineReadiness isReady() override;
    virtual void resume() override;
    virtual void startUpdate(double deltaTime) override;
    virtual void endUpdate(double deltaTime) override;
    virtual void pause() override;

    virtual long long getTimeSinceInit() override;
    virtual bool hasRequestExit() override;
protected:
    static std::unique_ptr<AndroidHack3dEngine> instance;

    virtual long long getSystemTime() override;
};

#endif