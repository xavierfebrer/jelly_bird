#ifndef COIN_PICK_DIAMOND_FX_H
#define COIN_PICK_DIAMOND_FX_H

#include "ConsumablePickFX.h"

class CoinPickDiamondFX : public ConsumablePickFX {
public:
    CoinPickDiamondFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                   const Vec2<> & renderPos);
    virtual ~CoinPickDiamondFX() override;
};

#endif