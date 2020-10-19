#ifndef MUSIC_H
#define MUSIC_H

#include "BaseInclude.h"
#include "Resource.h"

class Music : public Resource {
public:
    Music(const std::string & path);
    virtual ~Music();

    virtual bool play() = 0;
    virtual bool stop() = 0;
    virtual float getVolume() = 0;
    virtual void setVolume(float volume) = 0;
protected:
    std::string path;
};

#endif