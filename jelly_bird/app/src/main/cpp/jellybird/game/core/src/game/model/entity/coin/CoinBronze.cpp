#include "../../../../../include/CoinBronze.h"
#include "../../../../../include/CoinPickBronzeFX.h"

const long CoinBronze::VALUE = 1;
const double CoinBronze::ENERGY = CoinBronze::VALUE * 0.1;

CoinBronze::CoinBronze(GameWorld & gameWorld, double zOrder, double centerX, double centerY) : Consumable(
        gameWorld, zOrder, centerX, centerY, SIZE.x, SIZE.y, RENDER_SIZE.x, RENDER_SIZE.y, VALUE, ENERGY) {
}

CoinBronze::~CoinBronze() {
}

void CoinBronze::create() {
    animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
            AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                    gameWorld.game.gameAssets->tRsCoinBronze, 0.075));
    animation->randomizeCurrentStep();
    shader = gameWorld.shader;
    qTRObs = gameWorld.game.gameAssets->qTRCoinBronze.get();
}

void CoinBronze::collision(Entity * other) {
    Consumable::collision(other);
    gameWorld.addEntity(std::make_shared<CoinPickBronzeFX>(gameWorld, zOrder, shader, pos));
}