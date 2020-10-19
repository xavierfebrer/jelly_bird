#ifndef ASSETS_H
#define ASSETS_H

#include "BaseComponent.h"
#include "QuadTexture2D.h"

class Assets : public BaseComponent<> {
public:
    static const std::string PATH_ASSETS;
    static const std::string PATH_IMAGE;
    static const std::string PATH_AUDIO;
    static const std::string PATH_MUSIC;
    static const std::string PATH_SOUND;
    static const std::string PATH_SHADER;

    Assets();
    virtual ~Assets() override;
};

#endif