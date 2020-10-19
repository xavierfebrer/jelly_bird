#ifndef COIN_GOLD_H
#define COIN_GOLD_H

#include "Consumable.h"

class CoinGold : public Consumable {
public:
    static const long VALUE;
    static const double ENERGY;

    CoinGold(GameWorld & gameWorld, double zOrder, double centerX, double centerY);
    virtual ~CoinGold() override;

    virtual void create() override;
    virtual void collision(Entity * other) override;
};

#endif