#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Entity.h"

class Background : public Entity {
public:
    static const Vec2<double> RENDERING_SIZE;

    Texture2DShader * shader;
    QuadTexture2D * qBG;

    Background(GameWorld & gameWorld, double zOrder);
    virtual ~Background();

    virtual void create() override;
    virtual void resume() override;
    virtual void pause() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void collision(Entity * other) override;
    virtual void setInitialOffset(float deltaX, float deltaY);
    virtual void addInitialOffset(float deltaX, float deltaY);
    virtual void setOffset(float deltaX, float deltaY);
    virtual void addOffset(float deltaX, float deltaY);
protected:
    glm::vec2 initialOffset;
    glm::vec2 offset;
};

#endif