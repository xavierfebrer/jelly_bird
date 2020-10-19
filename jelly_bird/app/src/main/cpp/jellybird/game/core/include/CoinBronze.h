#ifndef COIN_BRONZE_H
#define COIN_BRONZE_H

#include "Consumable.h"

class CoinBronze : public Consumable {
public:
    static const long VALUE;
    static const double ENERGY;

    CoinBronze(GameWorld & gameWorld, double zOrder, double centerX, double centerY);
    virtual ~CoinBronze() override;

    virtual void create() override;
    virtual void collision(Entity * other) override;
};

#endif