#include "../../../../../include/Cherry.h"
#include "../../../../../include/CherryPickFX.h"

const Vec2<> Cherry::RENDER_SIZE = Vec2<>(16 * Constants::PIXEL_SIZE_W_UNIT,
                                                           16 * Constants::PIXEL_SIZE_W_UNIT);
const Vec2<> Cherry::SIZE = Vec2<>(10 * Constants::PIXEL_SIZE_W_UNIT,
                                                    12 * Constants::PIXEL_SIZE_W_UNIT);
const long Cherry::VALUE = 0;
const double Cherry::ENERGY = 20;

Cherry::Cherry(GameWorld & gameWorld, double zOrder, double centerX, double centerY) : Consumable(
        gameWorld, zOrder, centerX, centerY, SIZE.x, SIZE.y, RENDER_SIZE.x, RENDER_SIZE.y, VALUE, ENERGY) {
}

Cherry::~Cherry() {
}

void Cherry::create() {
    animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
            AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                    gameWorld.game.gameAssets->tRsCherry, 0.075));
    animation->randomizeCurrentStep();
    shader = gameWorld.shader;
    qTRObs = gameWorld.game.gameAssets->qTRCherry.get();
}

void Cherry::collision(Entity * other) {
    Consumable::collision(other);
    gameWorld.addEntity(std::make_shared<CherryPickFX>(gameWorld, zOrder, shader, pos));
}
