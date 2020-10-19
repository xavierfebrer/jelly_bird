#ifndef ANDROID_OPEN_SL_ES_SOUND_QUEUE_H
#define ANDROID_OPEN_SL_ES_SOUND_QUEUE_H

#include "../../../engine/core/include/BaseInclude.h"
#include <android_native_app_glue.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "AndroidOpenSLESSound.h"

class AndroidOpenSLESSoundQueue {
public:
    AndroidOpenSLESSoundQueue();
    virtual ~AndroidOpenSLESSoundQueue();

    bool init(SLEngineItf engine, SLObjectItf outputMixObj);
    void finalize();
    bool playSound(AndroidOpenSLESSound* sound);
private:
    SLObjectItf mPlayerObj;
    SLPlayItf mPlayer;
    SLBufferQueueItf mPlayerQueue;
    SLVolumeItf mPlayerVolume;

    bool checkError(SLuint32 result);
};

#endif