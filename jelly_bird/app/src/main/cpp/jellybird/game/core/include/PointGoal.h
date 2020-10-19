#ifndef POINT_GOAL_H
#define POINT_GOAL_H

#include "Entity.h"
#include "Wall.h"

class PointGoal : public Entity {
public:
    static const int DEFAULT_POINTS;

    double goalX;
    int points;

    PointGoal(GameWorld & gameWorld, double zOrder, double goalX, int points = DEFAULT_POINTS);
    virtual ~PointGoal() override;

    virtual void create() override;
    virtual void resume() override;
    virtual void pause() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void collision(Entity * other) override;
};

#endif