#ifndef COIN_PICK_GOLD_FX_H
#define COIN_PICK_GOLD_FX_H

#include "ConsumablePickFX.h"

class CoinPickGoldFX : public ConsumablePickFX {
public:
    CoinPickGoldFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                   const Vec2<> & renderPos);
    virtual ~CoinPickGoldFX() override;
};

#endif