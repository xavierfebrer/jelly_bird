#include "../../../../../include/CoinPickBronzeFX.h"

CoinPickBronzeFX::CoinPickBronzeFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                               const Vec2<> & renderPos) : ConsumablePickFX(gameWorld, zOrder, shader,
                                                                      Rect<>(renderPos.x,
                                                                             renderPos.y,
                                                                             RENDERING_SIZE.x * 1.0,
                                                                             RENDERING_SIZE.y * 1.0),
                                                                      gameWorld.game.gameAssets
                                                                              ->tRsCoinPickBronze) {

}

CoinPickBronzeFX::~CoinPickBronzeFX() {
}
