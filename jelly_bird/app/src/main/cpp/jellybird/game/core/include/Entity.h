#ifndef ENTITY_H
#define ENTITY_H

#include "../../../engine/core/include/BaseInclude.h"
#include "../../../engine/core/include/Game.h"
#include "GameWorld.h"

class Entity {
public:
    static const double DEFAULT_Z_ORDER;

    double zOrder;
    bool removed;

    Entity(GameWorld & gameWorld, double zOrder = DEFAULT_Z_ORDER);
    virtual ~Entity();

    virtual void create() = 0;
    virtual void resume() = 0;
    virtual void pause() = 0;
    virtual void update(double deltaTime) = 0;
    virtual void render(double deltaTime) = 0;
    virtual void collision(Entity * other) = 0;
protected:
    GameWorld & gameWorld;
};

#endif