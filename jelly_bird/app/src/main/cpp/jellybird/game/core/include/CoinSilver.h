#ifndef COIN_SILVER_H
#define COIN_SILVER_H

#include "Consumable.h"

class CoinSilver : public Consumable {
public:
    static const long VALUE;
    static const double ENERGY;

    CoinSilver(GameWorld & gameWorld, double zOrder, double centerX, double centerY);
    virtual ~CoinSilver() override;

    virtual void create() override;
    virtual void collision(Entity * other) override;
};

#endif