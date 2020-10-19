#ifndef FX_H
#define FX_H

#include "Entity.h"
#include "../../../engine/core/include/QuadTexture2D.h"
#include "../../../engine/core/include/Color.h"
#include "../../../engine/core/include/Animation.h"
#include "../../../engine/core/include/AnimationStep.h"
#include "../../../engine/core/include/Hack3dEngine.h"

class FX : public Entity {
public:

    FX(GameWorld & gameWorld, double zOrder);
    virtual ~FX() override;

    virtual void create() override;
    virtual void resume() override;
    virtual void pause() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void collision(Entity * other) override;

    virtual bool hasEnded() = 0;
};

#endif