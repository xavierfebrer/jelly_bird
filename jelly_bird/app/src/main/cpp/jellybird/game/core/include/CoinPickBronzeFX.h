#ifndef COIN_PICK_BRONZE_FX_H
#define COIN_PICK_BRONZE_FX_H

#include "ConsumablePickFX.h"

class CoinPickBronzeFX : public ConsumablePickFX {
public:
    CoinPickBronzeFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                   const Vec2<> & renderPos);
    virtual ~CoinPickBronzeFX() override;
};

#endif