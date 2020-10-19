#include "../../../include/AndroidOpenSLESSound.h"
#include "../../../include/AndroidHack3dEngine.h"

const float AndroidOpenSLESSound::DEFAULT_VOLUME = 1.0f;

AndroidOpenSLESSound::AndroidOpenSLESSound(android_app * app, const std::string & path,
                                           bool pathFromAssets) : Sound(path), app(app),
                                                                  pathFromAssets(pathFromAssets),
                                                                  volume(DEFAULT_VOLUME) {
}

AndroidOpenSLESSound::~AndroidOpenSLESSound() {
    unLoad();
}

bool AndroidOpenSLESSound::load() {
    if(!loaded) {
        if(!open()) {
            close();
            loaded = false;
            return loaded;
        }
        std::string suffixWav = ".wav";
        off_t readAssets;
        if(path.rfind(suffixWav) == (path.size() - suffixWav.size())) {
            wav_hdr wavHeader;
            int headerSize = sizeof(wav_hdr);
            off_t headerRead = AAsset_read(asset, &wavHeader, headerSize);
            if(headerRead != headerSize) {
                close();
                unLoad();
                loaded = false;
                return loaded;
            }
            if(wavHeader.AudioFormat != 1               // 1 = PCM
               || wavHeader.NumOfChan != 1              // 1 = mono
               || wavHeader.SamplesPerSec != 44100      // 44100 sampling frequency
               //|| wavHeader.bytesPerSec != 44100        // 44100 bytes per second
               || wavHeader.blockAlign != 2             // 2 = 16-bit mono
               || wavHeader.bitsPerSample != 16) {      // 16 bits per sample
                close();
                unLoad();
                loaded = false;
                return loaded;
            }
            length = AAsset_getRemainingLength(asset);
            buffer = new int64_t[length];
            readAssets = AAsset_read(asset, buffer, length);
            if(readAssets != length) {
                close();
                unLoad();
                loaded = false;
                return loaded;
            }
        } else {
            close();
            unLoad();
            loaded = false;
            return loaded;
        }
        close();
        loaded = true;
    }
    return loaded;
}

bool AndroidOpenSLESSound::unLoad() {
    if(loaded) {
        delete[] buffer;
        buffer = NULL;
        length = 0;
        loaded = false;
    }
    return !loaded;
}

bool AndroidOpenSLESSound::play() {
    return AndroidHack3dEngine::get().audio().playSound(this);
}

bool AndroidOpenSLESSound::rewind() {
    return false;
}

bool AndroidOpenSLESSound::pause() {
    return false;
}

bool AndroidOpenSLESSound::stop() {
    return false;
}

bool AndroidOpenSLESSound::isPlaying() {
    return false;
}

bool AndroidOpenSLESSound::isPaused() {
    return false;
}

bool AndroidOpenSLESSound::isStopped() {
    return false;
}

float AndroidOpenSLESSound::getVolume() {
    return volume;
}

bool AndroidOpenSLESSound::setVolume(float volume) {
    this->volume = volume;
    return true;
}

bool AndroidOpenSLESSound::getLooping() {
    return false;
}

bool AndroidOpenSLESSound::setLooping(bool loop) {
    return false;
}

float AndroidOpenSLESSound::getPitch() {
    return 0;
}

bool AndroidOpenSLESSound::setPitch(float pitch) {
    return false;
}

bool AndroidOpenSLESSound::open() {
    asset = AAssetManager_open(app->activity->assetManager, path.c_str(), AASSET_MODE_UNKNOWN);
    return asset != NULL;
}

void AndroidOpenSLESSound::close() {
    if(asset != NULL) {
        AAsset_close(asset);
        asset = NULL;
    }
}
