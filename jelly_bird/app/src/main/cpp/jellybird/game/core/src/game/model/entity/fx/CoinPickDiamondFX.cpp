#include "../../../../../include/CoinPickDiamondFX.h"

CoinPickDiamondFX::CoinPickDiamondFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                               const Vec2<> & renderPos) : ConsumablePickFX(gameWorld, zOrder, shader,
                                                                      Rect<>(renderPos.x,
                                                                             renderPos.y,
                                                                             RENDERING_SIZE.x * 3.00,
                                                                             RENDERING_SIZE.y * 3.00),
                                                                      gameWorld.game.gameAssets
                                                                              ->tRsCoinPickDiamond) {

}

CoinPickDiamondFX::~CoinPickDiamondFX() {
}
