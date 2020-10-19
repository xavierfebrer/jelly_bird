#include "../../../../../include/CoinGold.h"
#include "../../../../../include/CoinPickGoldFX.h"

const long CoinGold::VALUE = 5;
const double CoinGold::ENERGY = CoinGold::VALUE * 0.1;

CoinGold::CoinGold(GameWorld & gameWorld, double zOrder, double centerX, double centerY) : Consumable(
        gameWorld, zOrder, centerX, centerY, SIZE.x, SIZE.y, RENDER_SIZE.x, RENDER_SIZE.y, VALUE, ENERGY) {
}

CoinGold::~CoinGold() {
}

void CoinGold::create() {
    animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
            AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                    gameWorld.game.gameAssets->tRsCoinGold, 0.075));
    animation->randomizeCurrentStep();
    shader = gameWorld.shader;
    qTRObs = gameWorld.game.gameAssets->qTRCoinGold.get();
}

void CoinGold::collision(Entity * other) {
    Consumable::collision(other);
    gameWorld.addEntity(std::make_shared<CoinPickGoldFX>(gameWorld, zOrder, shader, pos));
}
