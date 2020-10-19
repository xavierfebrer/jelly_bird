#ifndef CHERRY_PICK_FX_H
#define CHERRY_PICK_FX_H

#include "ConsumablePickFX.h"

class CherryPickFX : public ConsumablePickFX {
public:
    CherryPickFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                   const Vec2<> & renderPos);
    virtual ~CherryPickFX() override;
};

#endif