#ifndef ANDROID_OPEN_SL_ES_SOUND_H
#define ANDROID_OPEN_SL_ES_SOUND_H

#include "../../core/include/Sound.h"
#include <android_native_app_glue.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

typedef struct WAV_HEADER {
    /* RIFF Chunk Descriptor */
    uint8_t RIFF[4];        // RIFF Header Magic header
    uint32_t ChunkSize;      // RIFF Chunk Size
    uint8_t WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t fmt[4];         // FMT header
    uint32_t Subchunk1Size;  // Size of the fmt chunk
    uint16_t AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t bytesPerSec;    // bytes per second
    uint16_t blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t Subchunk2ID[4]; // "data"  string
    uint32_t Subchunk2Size;  // Sampled data length
} wav_hdr;

class AndroidOpenSLESSound : public Sound {
public:
    static const float DEFAULT_VOLUME;

    android_app * app;
    int64_t * buffer;
    off_t length;

    AndroidOpenSLESSound(android_app * app, const std::string & path, bool pathFromAssets);
    virtual ~AndroidOpenSLESSound() override;

    virtual bool load() override;
    virtual bool unLoad() override;

    virtual bool play() override;
    virtual bool rewind() override;
    virtual bool pause() override;
    virtual bool stop() override;
    virtual bool isPlaying() override;
    virtual bool isPaused() override;
    virtual bool isStopped() override;
    virtual float getVolume() override;
    virtual bool setVolume(float volume) override;
    virtual bool getLooping() override;
    virtual bool setLooping(bool loop) override;
    virtual float getPitch() override;
    virtual bool setPitch(float pitch) override;
protected:
    bool pathFromAssets;
    AAsset * asset;
    float volume;

    virtual bool open();
    virtual void close();
};

#endif