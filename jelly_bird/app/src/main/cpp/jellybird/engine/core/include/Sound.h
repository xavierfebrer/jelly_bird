#ifndef SOUND_H
#define SOUND_H

#include "BaseInclude.h"
#include "Resource.h"

class Sound : public Resource {
public:
    Sound(const std::string & path);
    virtual ~Sound();

    virtual bool play() = 0;
    virtual bool rewind() = 0;
    virtual bool pause() = 0;
    virtual bool stop() = 0;
    virtual bool isPlaying() = 0;
    virtual bool isPaused() = 0;
    virtual bool isStopped() = 0;
    virtual float getVolume() = 0;
    virtual bool setVolume(float volume) = 0;
    virtual bool getLooping() = 0;
    virtual bool setLooping(bool loop) = 0;
    virtual float getPitch() = 0;
    virtual bool setPitch(float pitch) = 0;
protected:
    std::string path;
};

#endif