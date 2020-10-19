#include "../../../../../../include/Dirt1x1.h"
#include "../../../../../../../../engine/core/include/Hack3dEngine.h"
#include "../../../../../../include/GameAssets.h"
#include "../../../../../../include/Bird.h"

const Vec2<double> Dirt1x1::RENDER_SIZE = Vec2<double>(20 * Constants::PIXEL_SIZE_W_UNIT,
                                                        20 * Constants::PIXEL_SIZE_W_UNIT);
const Vec2<double> Dirt1x1::SIZE = Vec2<double>(10 * Constants::PIXEL_SIZE_W_UNIT,
                                                 10 * Constants::PIXEL_SIZE_W_UNIT);
const Color Dirt1x1::DEFAULT_TINT = Color(1.0, 1.0, 1.0, 1.0);

Dirt1x1::Dirt1x1(GameWorld & gameWorld, double zOrder, double centerX, double centerY) : Obstacle(
        gameWorld, zOrder, centerX, centerY, SIZE.x, SIZE.y, RENDER_SIZE.x, RENDER_SIZE.y, DEFAULT_TINT) {
}

Dirt1x1::~Dirt1x1() {
}

void Dirt1x1::create() {
    Obstacle::create();
    animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
            AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                    gameWorld.game.gameAssets->tRsDirt1x1, Util::random(0.15, 0.75)));
    shader = gameWorld.shader;
    qTRObs = gameWorld.game.gameAssets->qTRDirt1x1.get();
}