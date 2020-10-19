#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Obstacle.h"

class Consumable : public Obstacle {
public:
    static const Vec2<double> RENDER_SIZE;
    static const Vec2<double> SIZE;
    static const Color DEFAULT_TINT;
    long value;
    double energy;

    Consumable(GameWorld & gameWorld, double zOrder, double centerX, double centerY, double sizeX, double sizeY, double renderSizeX, double renderSizeY, long value, double energy);
    virtual ~Consumable() override;

    void collision(Entity * other) override;
};

#endif