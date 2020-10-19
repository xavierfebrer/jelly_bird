#include "../../../include/AndroidOpenSLESMusic.h"
#include "../../../include/AndroidHack3dEngine.h"

const float AndroidOpenSLESMusic::DEFAULT_VOLUME = 1.0f;

AndroidOpenSLESMusic::AndroidOpenSLESMusic(android_app * app, const std::string & path,
                                           bool pathFromAssets) : Music(path), app(app),
                                                                  pathFromAssets(pathFromAssets),
                                                                  volume(DEFAULT_VOLUME),
                                                                  mBGMusicPlayerObj(NULL),
                                                                  mBGMusicPlayer(NULL),
                                                                  mBGMusicPlayerSeek(NULL) {
}

AndroidOpenSLESMusic::~AndroidOpenSLESMusic() {
    unLoad();
}

bool AndroidOpenSLESMusic::load() {
    if(!loaded) {
        loaded = true;
    }
    return loaded;
}

bool AndroidOpenSLESMusic::unLoad() {
    if(loaded) {
        stop();
        loaded = false;
    }
    return !loaded;
}

bool AndroidOpenSLESMusic::play() {
    stop();
    SLresult result;
    if(!pathFromAssets) {
        throw -1;
    }
    AndroidOpenSLESAudio & audio = AndroidHack3dEngine::get().audio();
    ResourceDescriptor descriptor = audio.getDescriptor(path, pathFromAssets);
    if(descriptor.mDescriptor < 0) {
        return false;
    }
    SLDataLocator_AndroidFD dataLocatorIn;
    dataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
    dataLocatorIn.fd = descriptor.mDescriptor;
    dataLocatorIn.offset = descriptor.mStart;
    dataLocatorIn.length = descriptor.mLength;
    SLDataFormat_MIME dataFormat;
    dataFormat.formatType = SL_DATAFORMAT_MIME;
    dataFormat.mimeType = NULL;
    dataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;
    SLDataSource dataSource;
    dataSource.pLocator = &dataLocatorIn;
    dataSource.pFormat = &dataFormat;
    SLDataLocator_OutputMix dataLocatorOut;
    dataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    dataLocatorOut.outputMix = audio.mOutputMixObj;
    SLDataSink dataSink;
    dataSink.pLocator = &dataLocatorOut;
    dataSink.pFormat = NULL;
    const SLuint32 bgmPlayerIIDCount = 3;
    const SLInterfaceID bgmPlayerIIDs[] = {SL_IID_PLAY, SL_IID_SEEK, SL_IID_VOLUME};
    const SLboolean bgmPlayerReqs[] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    if(checkError((*audio.mEngine)
                          ->CreateAudioPlayer(audio.mEngine, &mBGMusicPlayerObj, &dataSource,
                                              &dataSink, bgmPlayerIIDCount, bgmPlayerIIDs,
                                              bgmPlayerReqs))) {
        return false;
    }
    if(checkError((*mBGMusicPlayerObj)->Realize(mBGMusicPlayerObj, SL_BOOLEAN_FALSE))) {
        return false;
    }
    if(checkError(
            (*mBGMusicPlayerObj)->GetInterface(mBGMusicPlayerObj, SL_IID_PLAY, &mBGMusicPlayer))) {
        return false;
    }
    if(checkError((*mBGMusicPlayerObj)
                          ->GetInterface(mBGMusicPlayerObj, SL_IID_SEEK, &mBGMusicPlayerSeek))) {
        return false;
    }
    if(checkError((*mBGMusicPlayerSeek)
                          ->SetLoop(mBGMusicPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN))) {
        return false;
    }
    if(checkError((*mBGMusicPlayerObj)->GetInterface(mBGMusicPlayerObj, SL_IID_VOLUME, &mPlayerVolume))) {
        return false;
    }
    if(checkError((*mBGMusicPlayer)->SetPlayState(mBGMusicPlayer, SL_PLAYSTATE_PLAYING))) {
        return false;
    }

    applyVolume(volume);

    return true;
}

bool AndroidOpenSLESMusic::stop() {
    if(mBGMusicPlayer != NULL) {
        SLuint32 bgmPlayerState;
        (*mBGMusicPlayerObj)->GetState(mBGMusicPlayerObj, &bgmPlayerState);
        if(bgmPlayerState == SL_OBJECT_STATE_REALIZED) {
            (*mBGMusicPlayer)->SetPlayState(mBGMusicPlayer, SL_PLAYSTATE_PAUSED);
            (*mBGMusicPlayerObj)->Destroy(mBGMusicPlayerObj);
            mBGMusicPlayerObj = NULL;
            mBGMusicPlayer = NULL;
            mBGMusicPlayerSeek = NULL;
        }
    }
    return true;
}

bool AndroidOpenSLESMusic::checkError(SLuint32 result) {
    return result != SL_RESULT_SUCCESS;
}

float AndroidOpenSLESMusic::getVolume() {
    return volume;
}

void AndroidOpenSLESMusic::setVolume(float volume) {
    this->volume = volume;
    applyVolume(volume);
}

void AndroidOpenSLESMusic::applyVolume(float volume) {
    if(volume >= 0.00001){
        SLmillibel minVolume = SL_MILLIBEL_MIN;
        SLmillibel maxVolume;
        (*mPlayerVolume)->GetMaxVolumeLevel(mPlayerVolume, &maxVolume);
        SLmillibel rangeVolume = minVolume + ( (SLmillibel)((float) (maxVolume - minVolume) * volume) );
        int dBVolume = 20 * log2(volume) / log2(10);
        SLmillibel volume = dBVolume * 100; //1dB = 100mB
        (*mPlayerVolume)->SetVolumeLevel(mPlayerVolume, volume);
    } else {
        (*mPlayerVolume)->SetVolumeLevel(mPlayerVolume, SL_MILLIBEL_MIN);
    }
}
