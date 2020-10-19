#include "../include/Hack3dEngine.h"

#ifdef ENGINE_FLAVOR_ANDROID_1

#include "../../core_android/include/AndroidHack3dEngine.h"
const Hack3dEngineFlavor Hack3dEngine::flavor = Hack3dEngineFlavor::FlavorAndroid;

#endif

Hack3dEngine & Hack3dEngine::get() {
#ifdef ENGINE_FLAVOR_ANDROID_1
    return AndroidHack3dEngine::get();
#endif
}

void Hack3dEngine::destroy() {
#ifdef ENGINE_FLAVOR_ANDROID_1
    return AndroidHack3dEngine::destroy();
#endif
}

Hack3dEngine::Hack3dEngine() : renderEnabled(false), initialized(false), requestExit(false) {
}

Hack3dEngine::~Hack3dEngine() {
}

bool Hack3dEngine::isRenderEnabled() {
    return renderEnabled;
}

void Hack3dEngine::setRenderEnabled(bool enable) {
    renderEnabled = enable;
}
