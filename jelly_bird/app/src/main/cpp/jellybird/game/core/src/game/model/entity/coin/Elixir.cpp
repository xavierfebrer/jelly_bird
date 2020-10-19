#include "../../../../../include/Elixir.h"
#include "../../../../../include/ElixirPickFX.h"

const Vec2<> Elixir::RENDER_SIZE = Vec2<>(16 * Constants::PIXEL_SIZE_W_UNIT,
                                                           16 * Constants::PIXEL_SIZE_W_UNIT);
const Vec2<> Elixir::SIZE = Vec2<>(10 * Constants::PIXEL_SIZE_W_UNIT,
                                                    12 * Constants::PIXEL_SIZE_W_UNIT);
const long Elixir::VALUE = 0;
const double Elixir::ENERGY = 40;

Elixir::Elixir(GameWorld & gameWorld, double zOrder, double centerX, double centerY) : Consumable(
        gameWorld, zOrder, centerX, centerY, SIZE.x, SIZE.y, RENDER_SIZE.x, RENDER_SIZE.y, VALUE, ENERGY) {
}

Elixir::~Elixir() {
}

void Elixir::create() {
    animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
            AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                    gameWorld.game.gameAssets->tRsElixir, 0.075));
    animation->randomizeCurrentStep();
    shader = gameWorld.shader;
    qTRObs = gameWorld.game.gameAssets->qTRElixir.get();
}

void Elixir::collision(Entity * other) {
    Consumable::collision(other);
    gameWorld.addEntity(std::make_shared<ElixirPickFX>(gameWorld, zOrder, shader, pos));
}
