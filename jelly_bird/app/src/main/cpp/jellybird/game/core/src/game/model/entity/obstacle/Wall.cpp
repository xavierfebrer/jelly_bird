#include "../../../../../include/Wall.h"
#include "../../../../../../../engine/core/include/Hack3dEngine.h"
#include "../../../../../include/GameAssets.h"
#include "../../../../../include/Bird.h"

const Vec2<double> Wall::RENDER_SIZE = Vec2<double>(45 * Constants::PIXEL_SIZE_W_UNIT,
                                             270 * Constants::PIXEL_SIZE_W_UNIT);
const Vec2<double> Wall::SIZE = Vec2<double>(25 * Constants::PIXEL_SIZE_W_UNIT,
                                             250 * Constants::PIXEL_SIZE_W_UNIT);
const Color Wall::DEFAULT_TINT = Color(1.0, 1.0, 1.0, 1.0);

Wall::Wall(GameWorld & gameWorld, double zOrder, double centerX, double centerY) : Obstacle(
        gameWorld, zOrder, centerX, centerY, SIZE.x, SIZE.y, RENDER_SIZE.x, RENDER_SIZE.y, DEFAULT_TINT) {
}

Wall::~Wall() {
}

void Wall::create() {
    Obstacle::create();
    animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
            AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                    gameWorld.game.gameAssets->tRsWall, Util::random(0.15, 0.75)));
    shader = gameWorld.shader;
    qTRObs = gameWorld.game.gameAssets->qTRWall.get();
}
