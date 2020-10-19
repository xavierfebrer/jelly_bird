#ifndef WALL_H
#define WALL_H

#include "Obstacle.h"

class Wall : public Obstacle {
public:
    static const Vec2<double> RENDER_SIZE;
    static const Vec2<double> SIZE;
    static const Color DEFAULT_TINT;

    Wall(GameWorld & gameWorld, double zOrder, double centerX, double centerY);
    virtual ~Wall() override;

    virtual void create() override;
};

#endif