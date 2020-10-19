#ifndef CHERRY_H
#define CHERRY_H

#include "Consumable.h"

class Cherry : public Consumable {
public:
    static const Vec2<> RENDER_SIZE;
    static const Vec2<> SIZE;
    static const long VALUE;
    static const double ENERGY;

    Cherry(GameWorld & gameWorld, double zOrder, double centerX, double centerY);
    virtual ~Cherry() override;

    virtual void create() override;
    virtual void collision(Entity * other) override;
};

#endif