#ifndef AUDIO_H
#define AUDIO_H

#include "BaseComponent.h"

class Audio : public BaseComponent<> {
public:
    Audio();
    virtual ~Audio() override;
};

#endif