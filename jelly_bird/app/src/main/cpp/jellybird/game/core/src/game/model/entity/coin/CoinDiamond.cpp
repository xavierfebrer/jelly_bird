#include "../../../../../include/CoinDiamond.h"
#include "../../../../../include/CoinPickDiamondFX.h"

const Vec2<double> CoinDiamond::RENDER_SIZE = Vec2<double>(16 * Constants::PIXEL_SIZE_W_UNIT,
                                                    16 * Constants::PIXEL_SIZE_W_UNIT);
const Vec2<double> CoinDiamond::SIZE = Vec2<double>(14 * Constants::PIXEL_SIZE_W_UNIT,
                                             10 * Constants::PIXEL_SIZE_W_UNIT);
const long CoinDiamond::VALUE = 15;
const double CoinDiamond::ENERGY = CoinDiamond::VALUE * 0.1;

CoinDiamond::CoinDiamond(GameWorld & gameWorld, double zOrder, double centerX, double centerY) : Consumable(
        gameWorld, zOrder, centerX, centerY, SIZE.x, SIZE.y, RENDER_SIZE.x, RENDER_SIZE.y, VALUE, ENERGY) {
}

CoinDiamond::~CoinDiamond() {
}

void CoinDiamond::create() {
    animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
            AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                    gameWorld.game.gameAssets->tRsCoinDiamond, 0.075));
    animation->randomizeCurrentStep();
    shader = gameWorld.shader;
    qTRObs = gameWorld.game.gameAssets->qTRCoinDiamond.get();
}

void CoinDiamond::collision(Entity * other) {
    Consumable::collision(other);
    gameWorld.addEntity(std::make_shared<CoinPickDiamondFX>(gameWorld, zOrder, shader, pos));
}
