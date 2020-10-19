#include "../../../../../include/ElixirPickFX.h"

ElixirPickFX::ElixirPickFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                               const Vec2<> & renderPos) : ConsumablePickFX(gameWorld, zOrder, shader,
                                                                      Rect<>(renderPos.x,
                                                                             renderPos.y,
                                                                             RENDERING_SIZE.x * 4.00,
                                                                             RENDERING_SIZE.y * 4.00),
                                                                      gameWorld.game.gameAssets
                                                                              ->tRsElixirPick) {

}

ElixirPickFX::~ElixirPickFX() {
}
