#ifndef ELIXIR_PICK_FX_H
#define ELIXIR_PICK_FX_H

#include "ConsumablePickFX.h"

class ElixirPickFX : public ConsumablePickFX {
public:
    ElixirPickFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                   const Vec2<> & renderPos);
    virtual ~ElixirPickFX() override;
};

#endif