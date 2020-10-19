#include "../../../../../include/CoinPickSilverFX.h"

CoinPickSilverFX::CoinPickSilverFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                               const Vec2<> & renderPos) : ConsumablePickFX(gameWorld, zOrder, shader,
                                                                      Rect<>(renderPos.x,
                                                                             renderPos.y,
                                                                             RENDERING_SIZE.x * 1.50,
                                                                             RENDERING_SIZE.y * 1.50),
                                                                      gameWorld.game.gameAssets
                                                                              ->tRsCoinPickSilver) {

}

CoinPickSilverFX::~CoinPickSilverFX() {
}
