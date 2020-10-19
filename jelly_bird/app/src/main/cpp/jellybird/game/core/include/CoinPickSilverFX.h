#ifndef COIN_PICK_SILVER_FX_H
#define COIN_PICK_SILVER_FX_H

#include "ConsumablePickFX.h"

class CoinPickSilverFX : public ConsumablePickFX {
public:
    CoinPickSilverFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                   const Vec2<> & renderPos);
    virtual ~CoinPickSilverFX() override;
};

#endif