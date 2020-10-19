#ifndef ANDROID_OPEN_SL_ES_MUSIC_H
#define ANDROID_OPEN_SL_ES_MUSIC_H

#include "../../core/include/Music.h"
#include <android_native_app_glue.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <android/asset_manager.h>

class AndroidOpenSLESMusic : public Music {
public:
    static const float DEFAULT_VOLUME;

    android_app * app;

    AndroidOpenSLESMusic(android_app * app, const std::string & path, bool pathFromAssets);
    virtual ~AndroidOpenSLESMusic() override;

    virtual bool load() override;
    virtual bool unLoad() override;

    virtual bool play() override;
    virtual bool stop() override;
    virtual float getVolume() override;
    virtual void setVolume(float volume) override;
protected:
    bool pathFromAssets;
    AAsset * asset;
    float volume;
    SLObjectItf mBGMusicPlayerObj;
    SLPlayItf mBGMusicPlayer;
    SLSeekItf mBGMusicPlayerSeek;
    SLVolumeItf mPlayerVolume;

    bool checkError(SLuint32 result);
    void applyVolume(float volume);
};

#endif