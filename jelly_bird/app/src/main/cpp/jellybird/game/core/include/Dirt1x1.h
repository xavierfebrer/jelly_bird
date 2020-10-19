#ifndef DIRT_1X1_H
#define DIRT_1X1_H

#include "Obstacle.h"

class Dirt1x1 : public Obstacle {
public:
    static const Vec2<double> RENDER_SIZE;
    static const Vec2<double> SIZE;
    static const Color DEFAULT_TINT;

    Dirt1x1(GameWorld & gameWorld, double zOrder, double centerX, double centerY);
    virtual ~Dirt1x1() override;

    virtual void create() override;
};

#endif