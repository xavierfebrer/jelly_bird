#ifndef HACK3D_ENGINE_H
#define HACK3D_ENGINE_H

#ifndef ENGINE_FLAVOR

#define ENGINE_FLAVOR_ANDROID_1 // OpenGL
//#define ENGINE_FLAVOR_ANDROID_2 // Vulkan
//#define ENGINE_FLAVOR_WINDOWS_1 // OpenGL
//#define ENGINE_FLAVOR_WINDOWS_2 // Vulkan
//#define ENGINE_FLAVOR_WINDOWS_3 // DX12

#define ENGINE_FLAVOR

#define NANOS_IN_SECOND 1000000000
#endif


#include "BaseInclude.h"
#include "Input.h"
#include "Audio.h"
#include "Graphics.h"
#include "Assets.h"

enum class Hack3dEngineFlavor {
    FlavorAndroid
};

enum class Hack3dEngineReadiness {
    NOT_READY, READY, ERROR_INPUT, ERROR_AUDIO, ERROR_GRAPHICS, ERROR_ASSETS, ERROR_GENERIC
};

class Hack3dEngine {
public:
    static const Hack3dEngineFlavor flavor;

    static Hack3dEngine & get();
    static void destroy();

    std::vector<std::shared_ptr<BaseComponent<>>> modules;

    Hack3dEngine();
    virtual ~Hack3dEngine();

    virtual Input & input() = 0;
    virtual Audio & audio() = 0;
    virtual Graphics & graphics() = 0;
    virtual Assets & assets() = 0;

    virtual bool init() = 0;
    virtual bool isInitialized() = 0;
    virtual Hack3dEngineReadiness isReady() = 0;
    virtual void resume() = 0;
    virtual void startUpdate(double deltaTime) = 0;
    virtual void endUpdate(double deltaTime) = 0;
    virtual void pause() = 0;

    virtual long long getTimeSinceInit() = 0;
    virtual bool hasRequestExit() = 0;
    virtual bool isRenderEnabled();
    virtual void setRenderEnabled(bool enable);
protected:
    bool renderEnabled;
    bool initialized;
    bool requestExit;
    long long initTime;

    virtual long long getSystemTime() = 0;
};

#endif