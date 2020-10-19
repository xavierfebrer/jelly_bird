#include "../include/AndroidHack3dEngine.h"

std::unique_ptr<AndroidHack3dEngine> AndroidHack3dEngine::instance = std::unique_ptr<AndroidHack3dEngine>(
        nullptr);

AndroidHack3dEngine & AndroidHack3dEngine::get() {
    if(!instance) {
        instance = std::unique_ptr<AndroidHack3dEngine>(new AndroidHack3dEngine());
    }
    return *instance;
}

void AndroidHack3dEngine::destroy() {
    if(instance) {
        instance->modules.clear();
        instance->androidInput.reset();
        instance->androidAudio.reset();
        instance->androidGraphics.reset();
        instance->androidAssets.reset();
        instance.reset();
    }
}

AndroidHack3dEngine::AndroidHack3dEngine() : Hack3dEngine() {
}

AndroidHack3dEngine::~AndroidHack3dEngine() {
}

AndroidInput & AndroidHack3dEngine::input() {
    return *androidInput;
}

AndroidOpenSLESAudio & AndroidHack3dEngine::audio() {
    return *androidAudio;
}

AndroidGraphics & AndroidHack3dEngine::graphics() {
    return *androidGraphics;
}

AndroidAssets & AndroidHack3dEngine::assets() {
    return *androidAssets;
}

bool AndroidHack3dEngine::init() {
    if(!isInitialized()) {
        initialized = true;
        initTime = getSystemTime();
        androidInput = std::shared_ptr<AndroidInput>(new AndroidInput(app));
        androidAudio = std::shared_ptr<AndroidOpenSLESAudio>(new AndroidOpenSLESAudio(app));
        androidGraphics = std::shared_ptr<AndroidGraphics>(new AndroidGraphics(app));
        androidAssets = std::shared_ptr<AndroidAssets>(new AndroidAssets(app));
        modules.push_back(androidInput);
        modules.push_back(androidAudio);
        modules.push_back(androidGraphics);
        modules.push_back(androidAssets);
        for(auto & module : modules) {
            module->init();
        }
    }
    return initialized;
}

bool AndroidHack3dEngine::isInitialized() {
    return initialized;
}

Hack3dEngineReadiness AndroidHack3dEngine::isReady() {
    if(!isInitialized()) {
        return Hack3dEngineReadiness::NOT_READY;
    }
    BaseComponentReadiness modulesReady;
    for(auto & module : modules) {
        modulesReady = module->isReady();
        if(modulesReady == BaseComponentReadiness::ERROR_GENERIC) {
            return Hack3dEngineReadiness::ERROR_GENERIC;
        } else if(modulesReady == BaseComponentReadiness::NOT_READY) {
            return Hack3dEngineReadiness::NOT_READY;
        }
    }
    return Hack3dEngineReadiness::READY;
}

void AndroidHack3dEngine::resume() {
    for(auto & module : modules) {
        requestExit = requestExit || module->hasRequestExit();
    }
}

void AndroidHack3dEngine::startUpdate(double deltaTime) {
    for(auto & module : modules) {
        module->startUpdate(deltaTime);
        requestExit = requestExit || module->hasRequestExit();
    }
}

void AndroidHack3dEngine::endUpdate(double deltaTime) {
    for(auto & module : modules) {
        module->endUpdate(deltaTime);
        requestExit = requestExit || module->hasRequestExit();
    }
}

void AndroidHack3dEngine::pause() {
    for(auto & module : modules) {
        requestExit = requestExit || module->hasRequestExit();
    }
}

long long AndroidHack3dEngine::getSystemTime() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (long long) now.tv_sec * 1000000000LL + now.tv_nsec;
}

long long AndroidHack3dEngine::getTimeSinceInit() {
    return getSystemTime() - initTime;
}

bool AndroidHack3dEngine::hasRequestExit() {
    return requestExit;
}