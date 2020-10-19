#ifndef ANIMATION_FX_H
#define ANIMATION_FX_H

#include "FX.h"

class AnimationEndFX : public FX {
public:

    AnimationEndFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                   const Rect<> & renderSize, const std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> & animation);
    virtual ~AnimationEndFX() override;

    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual bool hasEnded() override;
protected:
    Texture2DShader * shader;
    Rect<> renderRect;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animation;
    QuadTextureRegion2D * qTRBird;
};

#endif