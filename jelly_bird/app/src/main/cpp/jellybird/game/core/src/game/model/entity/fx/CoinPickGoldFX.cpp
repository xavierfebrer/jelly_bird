#include "../../../../../include/CoinPickGoldFX.h"

CoinPickGoldFX::CoinPickGoldFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                               const Vec2<> & renderPos) : ConsumablePickFX(gameWorld, zOrder, shader,
                                                                      Rect<>(renderPos.x,
                                                                             renderPos.y,
                                                                             RENDERING_SIZE.x * 2.00,
                                                                             RENDERING_SIZE.y * 2.00),
                                                                      gameWorld.game.gameAssets
                                                                              ->tRsCoinPickGold) {

}

CoinPickGoldFX::~CoinPickGoldFX() {
}
