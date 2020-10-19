#include "../../../../../include/CoinSilver.h"
#include "../../../../../include/CoinPickSilverFX.h"

const long CoinSilver::VALUE = 2;
const double CoinSilver::ENERGY = CoinSilver::VALUE * 0.1;

CoinSilver::CoinSilver(GameWorld & gameWorld, double zOrder, double centerX, double centerY) : Consumable(
        gameWorld, zOrder, centerX, centerY, SIZE.x, SIZE.y, RENDER_SIZE.x, RENDER_SIZE.y, VALUE, ENERGY) {
}

CoinSilver::~CoinSilver() {
}

void CoinSilver::create() {
    animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
            AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                    gameWorld.game.gameAssets->tRsCoinSilver, 0.075));
    animation->randomizeCurrentStep();
    shader = gameWorld.shader;
    qTRObs = gameWorld.game.gameAssets->qTRCoinSilver.get();
}

void CoinSilver::collision(Entity * other) {
    Consumable::collision(other);
    gameWorld.addEntity(std::make_shared<CoinPickSilverFX>(gameWorld, zOrder, shader, pos));
}
