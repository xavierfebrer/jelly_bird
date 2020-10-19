#include "../../../../../include/Obstacle.h"
#include "../../../../../../../engine/core/include/Hack3dEngine.h"
#include "../../../../../include/GameAssets.h"
#include "../../../../../include/Bird.h"

Obstacle::Obstacle(GameWorld & gameWorld, double zOrder, double centerX, double centerY, double sizeX, double sizeY, double renderingSizeX, double renderingSizeY, const Color & tint)
        : Entity(gameWorld, zOrder), pos(centerX, centerY), size(sizeX, sizeY), renderingSize(renderingSizeX, renderingSizeY), tint(tint) {
}

Obstacle::~Obstacle() {
}

void Obstacle::create() {
}

void Obstacle::resume() {
}

void Obstacle::pause() {
}

void Obstacle::update(double deltaTime) {
    if (gameWorld.bird->pos.x - gameWorld.camera.getViewPort().x > pos.x) {
        removed = true;
    }

    // update resource stuff
    animation->update(deltaTime);
}

void Obstacle::render(double deltaTime) {
    qTRObs->textureRegion2D = animation->getCurrentStep().getItem().get();
    qTRObs->render(*shader, gameWorld.camera,
                pos.x - (renderingSize.x * 0.5),
                pos.y - (renderingSize.y * 0.5),
                -2,
                renderingSize.x,
                renderingSize.y);
}

void Obstacle::collision(Entity * other) {
}
