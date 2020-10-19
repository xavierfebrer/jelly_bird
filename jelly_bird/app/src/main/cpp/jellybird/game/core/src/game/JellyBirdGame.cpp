#include "../../include/JellyBirdGame.h"
#include "../../include/LogoScreen.h"
#include "../../../../engine/core/include/Hack3dEngine.h"

JellyBirdGame::JellyBirdGame(const std::shared_ptr<LogoAssets> & logoAssets,
                             const std::shared_ptr<MenuAssets> & menuAssets,
                             const std::shared_ptr<GameAssets> & gameAssets)
        : Game(), logoAssets(logoAssets), menuAssets(menuAssets), gameAssets(gameAssets),
          initialized(false), running(false), currentScreen(nullptr),
          newScreen(nullptr) {

}

JellyBirdGame::~JellyBirdGame() {
    if(newScreen) {
        newScreen.reset();
    }
    if(currentScreen) {
        currentScreen->pause();
        currentScreen.reset();
    }
    logoAssets->unLoad();
    menuAssets->unLoad();
    gameAssets->unLoad();
    Hack3dEngine::destroy();
}

bool JellyBirdGame::create() {
    return init() && waitForReadyState() && startGame();
}

bool JellyBirdGame::init() {
    if(!initialized) {
        initialized = false;
        running = false;
        Hack3dEngine & engine = Hack3dEngine::get();
        if(!engine.init()) {
            return false;
        }
        initialized = true;
    }
    return initialized;
}

bool JellyBirdGame::waitForReadyState() {
    Hack3dEngineReadiness engineReady;
    bool allReady = false;
    while(!allReady) {
        engineReady = Hack3dEngine::get().isReady();
        if(engineReady == Hack3dEngineReadiness::ERROR_GENERIC ||
           engineReady == Hack3dEngineReadiness::ERROR_INPUT ||
           engineReady == Hack3dEngineReadiness::ERROR_AUDIO ||
           engineReady == Hack3dEngineReadiness::ERROR_GRAPHICS ||
           engineReady == Hack3dEngineReadiness::ERROR_ASSETS) {
            return false;
        }
        allReady =
                engineReady == Hack3dEngineReadiness::READY;    // add all the readiness states here
    }
    return true;
}

bool JellyBirdGame::startGame() {
    running = true;
    setScreen(std::make_unique<LogoScreen>(*this));
    return true;
}

void JellyBirdGame::resume() {
    running = true;
    Hack3dEngine::get().resume();
    if(currentScreen) {
        currentScreen->resume();
    }
}

void JellyBirdGame::loop() {
    Hack3dEngine & engine = Hack3dEngine::get();
    if(initialized) {
        if(running) {
            checkNewScreen();
            if(currentScreen) {
                currentTime = engine.getTimeSinceInit();
                double deltaTime = std::min(((currentTime - prevTime) / ((double) 1000000000LL)),
                                            Constants::MAX_DELTA_TIME_FRAME);
                prevTime = currentTime;
                update(deltaTime);
                if(engine.isRenderEnabled()) {
                    render(deltaTime);
                }
                waitForTargetFPS();
            }
        }
    }
}

void JellyBirdGame::update(double deltaTime) {
    Hack3dEngine & engine = Hack3dEngine::get();
    engine.startUpdate(deltaTime);
    if(currentScreen) {
        currentScreen->update(deltaTime);
    }
    engine.endUpdate(deltaTime);
    if(engine.hasRequestExit()) { exit(); }
}

void JellyBirdGame::render(double deltaTime) {
    Hack3dEngine & engine = Hack3dEngine::get();
    engine.graphics().startRender(deltaTime);
    if(currentScreen) {
        currentScreen->render(deltaTime);
    }
    engine.graphics().endRender(deltaTime);
}

void JellyBirdGame::waitForTargetFPS() {
}

void JellyBirdGame::pause() {
    running = false;
    Hack3dEngine::get().pause();
    if(currentScreen) {
        currentScreen->pause();
    }
}

void JellyBirdGame::resize(double width, double height) {
    if(currentScreen) {
        currentScreen->resize(width, height);
    }
}

void JellyBirdGame::setScreen(std::unique_ptr<BaseScreen> newScreen) {
    this->newScreen = std::move(newScreen);
}

void JellyBirdGame::checkNewScreen() {
    if(newScreen) {
        if(currentScreen) {
            currentScreen->pause();
            currentScreen.reset();
        }
        currentScreen = std::move(newScreen);
        currentScreen->create();
        currentScreen->resume();
    }
}
