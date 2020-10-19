#include "../../../../include/BaseScreen.h"
#include "../../../../include/JellyBirdGame.h"

BaseScreen::BaseScreen(JellyBirdGame & game) : Screen<JellyBirdGame>(game),
                                               camera(Camera(CameraProjection::Orthogonal,
                                                             Vec2<float>())) {
}

BaseScreen::~BaseScreen() {
}

void BaseScreen::create() {
    setupCamera();
    initViews();
}

void BaseScreen::resume() {
    viewManager.resume();
}

void BaseScreen::update(double deltaTime) {
    viewManager.update(deltaTime, camera);
}

void BaseScreen::render(double deltaTime) {
    if(shader != nullptr) {
        viewManager.render(deltaTime, camera, *shader);
    }
}

void BaseScreen::resize(double width, double height) {
    viewManager.resize(width, height);
}

void BaseScreen::pause() {
    viewManager.pause();
}

void BaseScreen::setupCamera() {
    Hack3dEngine & engine = Hack3dEngine::get();
    Graphics & graphics = engine.graphics();
    Vec2<int> windowSizeT = graphics.getWindowSize();
    Vec2<float> windowSize(windowSizeT.x, windowSizeT.y);

    double maxViewPortWorldUnits = Constants::MAX_VIEW_PORT_WORLD_UNITS_HEIGHT;
    Vec2<float> viewPort;

    /*if (windowSize.x > windowSize.y) {
        viewPort = Vec2<double>((windowSize.x / windowSize.y) * minViewPortWorldUnits, minViewPortWorldUnits);
    } else {
        viewPort = Vec2<double>(minViewPortWorldUnits, (windowSize.y / windowSize.x) * minViewPortWorldUnits);
    }*/
    if(windowSize.x > windowSize.y) {
        viewPort = Vec2<float>((windowSize.x / windowSize.y) * maxViewPortWorldUnits,
                               maxViewPortWorldUnits);
    } else {
        viewPort = Vec2<float>((windowSize.x / windowSize.y) * maxViewPortWorldUnits,
                               maxViewPortWorldUnits);
    }

    camera = Camera(CameraProjection::Orthogonal, viewPort);    // TODO create camera 2D class?
    camera.setPosition(glm::vec3(0.0f, 0.0f, Constants::Z_CAMERA_WORLD_2D));
    camera.setYaw(-90.0f);
    camera.setPitch(0.0f);
    camera.updateCameraVectors();
}
