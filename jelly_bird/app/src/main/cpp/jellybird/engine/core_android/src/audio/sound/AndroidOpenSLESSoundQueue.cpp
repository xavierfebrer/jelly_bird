#include "../../../include/AndroidOpenSLESSoundQueue.h"

AndroidOpenSLESSoundQueue::AndroidOpenSLESSoundQueue() {
}

AndroidOpenSLESSoundQueue::~AndroidOpenSLESSoundQueue() {
    finalize();
}

bool AndroidOpenSLESSoundQueue::init(SLEngineItf pEngine, SLObjectItf pOutputMixObj) {
    // Set-up sound audio source.
    SLDataLocator_AndroidSimpleBufferQueue dataLocatorIn;
    dataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
    // At most one buffer in the queue.
    dataLocatorIn.numBuffers = 1;
    SLDataFormat_PCM dataFormat;
    dataFormat.formatType = SL_DATAFORMAT_PCM;
    dataFormat.numChannels = 1; // Mono sound.
    dataFormat.samplesPerSec = SL_SAMPLINGRATE_44_1;
    dataFormat.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
    dataFormat.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
    dataFormat.channelMask = SL_SPEAKER_FRONT_CENTER;
    dataFormat.endianness = SL_BYTEORDER_LITTLEENDIAN;
    SLDataSource dataSource;
    dataSource.pLocator = &dataLocatorIn;
    dataSource.pFormat = &dataFormat;
    SLDataLocator_OutputMix dataLocatorOut;
    dataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    dataLocatorOut.outputMix = pOutputMixObj;
    SLDataSink dataSink;
    dataSink.pLocator = &dataLocatorOut;
    dataSink.pFormat = NULL;

    const SLuint32 soundPlayerIIDCount = 3;
    const SLInterfaceID soundPlayerIIDs[] = {SL_IID_PLAY, SL_IID_BUFFERQUEUE, SL_IID_VOLUME};
    const SLboolean soundPlayerReqs[] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    if(checkError((*pEngine)->CreateAudioPlayer(pEngine, &mPlayerObj, &dataSource, &dataSink,
                                                soundPlayerIIDCount, soundPlayerIIDs,
                                                soundPlayerReqs))) {
        return false;
    }
    if(checkError((*mPlayerObj)->Realize(mPlayerObj, SL_BOOLEAN_FALSE))) {
        return false;
    }
    if(checkError((*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_PLAY, &mPlayer))) {
        return false;
    }
    if(checkError((*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_BUFFERQUEUE, &mPlayerQueue))) {
        return false;
    }
    if(checkError((*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_VOLUME, &mPlayerVolume))) {
        return false;
    }
    if(checkError((*mPlayer)->SetPlayState(mPlayer, SL_PLAYSTATE_PLAYING))) {
        return false;
    }
    return true;
}

void AndroidOpenSLESSoundQueue::finalize() {
    if(mPlayerObj != NULL) {
        (*mPlayerObj)->Destroy(mPlayerObj);
        mPlayerObj = NULL;
        mPlayer = NULL;
        mPlayerQueue = NULL;
    }
}

bool AndroidOpenSLESSoundQueue::playSound(AndroidOpenSLESSound * sound) {
    SLuint32 playerState;
    (*mPlayerObj)->GetState(mPlayerObj, &playerState);
    if(playerState == SL_OBJECT_STATE_REALIZED) {
        int64_t * buffer = sound->buffer;
        off_t length = sound->length;
        // Removes any sound from the queue.
        if(checkError((*mPlayerQueue)->Clear(mPlayerQueue))) {
            return false;
        }

        if(sound->getVolume() >= 0.00001){
            SLmillibel minVolume = SL_MILLIBEL_MIN;
            SLmillibel maxVolume;
            (*mPlayerVolume)->GetMaxVolumeLevel(mPlayerVolume, &maxVolume);
            SLmillibel rangeVolume = minVolume + ( (SLmillibel)((float) (maxVolume - minVolume) * sound->getVolume()) );
            int dBVolume = 20 * log2(sound->getVolume()) / log2(10);
            SLmillibel volume = dBVolume * 100; //1dB = 100mB
            (*mPlayerVolume)->SetVolumeLevel(mPlayerVolume, volume);
        } else {
            (*mPlayerVolume)->SetVolumeLevel(mPlayerVolume, SL_MILLIBEL_MIN);
        }

        // Plays the new sound.
        if(checkError((*mPlayerQueue)->Enqueue(mPlayerQueue, buffer, length))) {
            return false;
        }
    }
    return true;
}

bool AndroidOpenSLESSoundQueue::checkError(SLuint32 result) {
    return result != SL_RESULT_SUCCESS;
}