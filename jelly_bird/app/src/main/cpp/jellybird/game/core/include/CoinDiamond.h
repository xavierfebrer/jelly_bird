#ifndef COIN_DIAMOND_H
#define COIN_DIAMOND_H

#include "Consumable.h"

class CoinDiamond : public Consumable {
public:
    static const Vec2<double> RENDER_SIZE;
    static const Vec2<double> SIZE;
    static const long VALUE;
    static const double ENERGY;

    CoinDiamond(GameWorld & gameWorld, double zOrder, double centerX, double centerY);
    virtual ~CoinDiamond() override;

    virtual void create() override;
    virtual void collision(Entity * other) override;
};

#endif