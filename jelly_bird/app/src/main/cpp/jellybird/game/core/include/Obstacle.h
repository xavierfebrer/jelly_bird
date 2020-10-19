#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Entity.h"
#include "../../../engine/core/include/QuadTexture2D.h"
#include "../../../engine/core/include/Animation.h"
#include "../../../engine/core/include/AnimationStep.h"

class Obstacle : public Entity {
public:
    Vec2<double> pos;
    Vec2<double> size;
    Vec2<double> renderingSize;
    Color tint;
    Texture2DShader * shader;
    QuadTextureRegion2D * qTRObs;
    std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animation;

    Obstacle(GameWorld & gameWorld, double zOrder, double x, double y, double sizeX, double sizeY, double renderingSizeX, double renderingSizeY, const Color & tint);
    virtual ~Obstacle() override;

    virtual void create() override;
    virtual void resume() override;
    virtual void pause() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void collision(Entity * other) override;
};

#endif