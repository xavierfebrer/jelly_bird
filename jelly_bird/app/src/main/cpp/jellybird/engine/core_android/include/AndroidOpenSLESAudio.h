#ifndef ANDROID_OPEN_SL_ES_AUDIO_H
#define ANDROID_OPEN_SL_ES_AUDIO_H

#include "../../core/include/Audio.h"
#include <android_native_app_glue.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "AndroidOpenSLESSound.h"
#include "AndroidOpenSLESSoundQueue.h"

struct ResourceDescriptor {
    int32_t mDescriptor;
    off_t mStart;
    off_t mLength;
};

class AndroidOpenSLESAudio : public Audio {
public:
    static const int QUEUE_COUNT;   // min 2

    android_app* app;
    SLObjectItf mEngineObj;
    SLEngineItf mEngine;
    SLObjectItf mOutputMixObj;
    SLObjectItf mBGMusicPlayerObj;
    SLPlayItf mBGMusicPlayer;
    SLSeekItf mBGMusicPlayerSeek;
    std::vector<std::shared_ptr<AndroidOpenSLESSoundQueue>> soundQueues;

    AndroidOpenSLESAudio(android_app* app);
    virtual ~AndroidOpenSLESAudio() override;

    virtual BaseComponentReadiness isReady() override;

    virtual bool load();
    virtual bool unLoad();
    virtual bool playSound(AndroidOpenSLESSound * sound);
    ResourceDescriptor getDescriptor(const std::string & path, bool pathFromAssets);
protected:

    bool checkError(SLuint32 result);
    bool checkErrorAndUnload(SLuint32 result);
};

#endif