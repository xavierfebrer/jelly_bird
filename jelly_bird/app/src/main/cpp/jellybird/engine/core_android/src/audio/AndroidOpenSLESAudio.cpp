#include "../../include/AndroidOpenSLESAudio.h"

const int AndroidOpenSLESAudio::QUEUE_COUNT = 4;

AndroidOpenSLESAudio::AndroidOpenSLESAudio(android_app * app)
        : Audio(), app(app), mEngineObj(NULL), mEngine(NULL), mOutputMixObj(NULL),
          mBGMusicPlayerObj(NULL), mBGMusicPlayer(NULL), mBGMusicPlayerSeek(NULL) {
}

AndroidOpenSLESAudio::~AndroidOpenSLESAudio() {
}

BaseComponentReadiness AndroidOpenSLESAudio::isReady() {
    return isInitialized() ? BaseComponentReadiness::READY : BaseComponentReadiness::NOT_READY;
}

bool AndroidOpenSLESAudio::load() {
    SLresult result;
    const SLuint32 engineMixIIDCount = 1;
    const SLInterfaceID engineMixIIDs[] = {SL_IID_ENGINE};
    const SLboolean engineMixReqs[] = {SL_BOOLEAN_TRUE};
    const SLuint32 outputMixIIDCount = 0;
    const SLInterfaceID outputMixIIDs[] = {};
    const SLboolean outputMixReqs[] = {};

    // Creates OpenSL ES engine and dumps its capabilities.
    if(checkErrorAndUnload(slCreateEngine(&mEngineObj, 0, NULL, engineMixIIDCount, engineMixIIDs,
                                          engineMixReqs))) {
        return false;
    }
    if(checkErrorAndUnload((*mEngineObj)->Realize(mEngineObj, SL_BOOLEAN_FALSE))) {
        return false;
    }
    if(checkErrorAndUnload((*mEngineObj)->GetInterface(mEngineObj, SL_IID_ENGINE, &mEngine))) {
        return false;
    }
    // Creates audio output.
    if(checkErrorAndUnload((*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj, outputMixIIDCount,
                                                       outputMixIIDs, outputMixReqs))) {
        return false;
    }
    if(checkErrorAndUnload((*mOutputMixObj)->Realize(mOutputMixObj, SL_BOOLEAN_FALSE))) {
        return false;
    }

    for(int i = 0; i < QUEUE_COUNT; ++i) {
        soundQueues.push_back(std::make_shared<AndroidOpenSLESSoundQueue>());
        if(!soundQueues[i]->init(mEngine, mOutputMixObj)) {
            return false;
        }
    }
    return true;
}

bool AndroidOpenSLESAudio::unLoad() {
    for(int i = 0; i < soundQueues.size(); ++i) {
        soundQueues[i]->finalize();
    }
    soundQueues.clear();
    if(mOutputMixObj != NULL) {
        (*mOutputMixObj)->Destroy(mOutputMixObj);
        mOutputMixObj = NULL;
    }
    if(mEngineObj != NULL) {
        (*mEngineObj)->Destroy(mEngineObj);
        mEngineObj = NULL;
        mEngine = NULL;
    }
    return true;
}

bool AndroidOpenSLESAudio::playSound(AndroidOpenSLESSound * sound) {
    std::shared_ptr<AndroidOpenSLESSoundQueue> currentSoundQueue = soundQueues.front();
    soundQueues.erase(soundQueues.begin());
    soundQueues.push_back(currentSoundQueue);
    return soundQueues.front()->playSound(sound);
}

bool AndroidOpenSLESAudio::checkError(SLuint32 result) {
    return result != SL_RESULT_SUCCESS;
}

bool AndroidOpenSLESAudio::checkErrorAndUnload(SLuint32 result) {
    if(checkError(result)) {
        unLoad();
        return true;
    }
    return false;
}

ResourceDescriptor AndroidOpenSLESAudio::getDescriptor(const std::string & path, bool pathFromAssets){
    if(!pathFromAssets){
        throw -1;
    }
    ResourceDescriptor lDescriptor = { -1, 0, 0 };
    AAsset* lAsset = AAssetManager_open(app->activity->assetManager, path.c_str(), AASSET_MODE_UNKNOWN);
    if (lAsset != NULL) {
        lDescriptor.mDescriptor = AAsset_openFileDescriptor(lAsset, &lDescriptor.mStart, &lDescriptor.mLength);
        AAsset_close(lAsset);
    } else {
        throw -1;
    }
    return lDescriptor;
}
