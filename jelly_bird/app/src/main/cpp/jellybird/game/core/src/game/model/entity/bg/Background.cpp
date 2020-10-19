#include "../../../../../include/Background.h"

const Vec2<double> Background::RENDERING_SIZE = Vec2<double>(1920 * Constants::PIXEL_SIZE_W_UNIT,
                                                       1080 * Constants::PIXEL_SIZE_W_UNIT);

Background::Background(GameWorld & gameWorld, double zOrder) : Entity(gameWorld, zOrder),
                                                               initialOffset(glm::vec2(0, 0)),
                                                               offset(glm::vec2(0, 0)) {
}

Background::~Background() {
}

void Background::create() {
    shader = gameWorld.shader;
    qBG = gameWorld.game.gameAssets->qGameGB.get();
    if(Util::random() > 0.5){
        qBG->texture2D = gameWorld.game.gameAssets->tGameBGDay.get();
    } else {
        qBG->texture2D = gameWorld.game.gameAssets->tGameBGNight.get();
    }
}

void Background::resume() {
}

void Background::pause() {
}

void Background::update(double deltaTime) {
}

void Background::render(double deltaTime) {
    glm::vec3 position = gameWorld.camera.getPosition();
    /*Vec2<float> viewPort = gameWorld.camera.getViewPort();
    Vec2<float> size(0.0, 0.0);
    Vec2<int> texture2DSize = qBG->texture2D->getSize();

    size.y = viewPort.y;
    size.x = (((float) texture2DSize.x) / ((float) texture2DSize.y)) * size.y;

    qBG->render(*shader, gameWorld.camera,
            position.x - (size.x * 0.5),
            position.y - (size.y * 0.5),
                -10,
                size.x,
                size.y,
                0.0, Vec2<>(1.0, 1.0),
                Vec2<>(0.0, 0.0),
                Color(1.0, 1.0, 1.0, 1.0),
                false, false,
                initialOffset + offset);*/
    qBG->render(*shader, gameWorld.camera,
                position.x - (RENDERING_SIZE.x * 0.5),
                position.y - (RENDERING_SIZE.y * 0.5),
                -10,
                RENDERING_SIZE.x,
                RENDERING_SIZE.y,
                0.0, Vec2<>(1.0, 1.0),
                Vec2<>(0.0, 0.0),
                Color(1.0, 1.0, 1.0, 1.0),
                false, false,
                initialOffset + offset);
}

void Background::collision(Entity * other) {
}

void Background::setInitialOffset(float x, float y) {
    initialOffset.x = x;
    initialOffset.y = y;
}

void Background::addInitialOffset(float x, float y) {
    initialOffset.x += x;
    initialOffset.y += y;
}

void Background::setOffset(float x, float y) {
    offset.x = x;
    offset.y = y;
}

void Background::addOffset(float x, float y) {
    offset.x += x;
    offset.y += y;
}
