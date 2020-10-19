#ifndef CONSUMABLE_PICK_FX_H
#define CONSUMABLE_PICK_FX_H

#include "AnimationEndFX.h"

class ExpEase;

class ConsumablePickFX : public AnimationEndFX {
public:
    static const Vec2<> RENDERING_SIZE;

    ConsumablePickFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
               const Rect<> & renderSize, std::vector<std::shared_ptr<TextureRegion2D>> & tRsPick);
    virtual ~ConsumablePickFX() override;

    virtual void render(double deltaTime) override;
protected:
    std::unique_ptr<ExpEase> easeFade;
};

#endif