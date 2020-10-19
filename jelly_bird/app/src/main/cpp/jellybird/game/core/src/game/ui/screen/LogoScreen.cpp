#include "../../../../include/LogoScreen.h"
#include "../../../../../../engine/core/include/Hack3dEngine.h"

LogoScreen::LogoScreen(JellyBirdGame & game) : BaseScreen(game) {
}

LogoScreen::~LogoScreen() {
}

void LogoScreen::create() {
    //Hack3dEngine::get().assets().logo->load();
    BaseScreen::create();
}

void LogoScreen::initViews() {
}

void LogoScreen::resume() {
    BaseScreen::resume();
}

void LogoScreen::update(double deltaTime) {
    BaseScreen::update(deltaTime);
    totalTime += deltaTime;
    if(totalTime > TARGET_TOTAL_TIME) {
        //Hack3dEngine::get().assets().logo->unLoad();
        openMainMenuScreen();
    }
}

void LogoScreen::render(double deltaTime) {
    Hack3dEngine::get().graphics().clearScreen(1.0f, 0.1f, 0.1f, 0.1f);
    BaseScreen::render(deltaTime);
}

void LogoScreen::pause() {
    BaseScreen::pause();
}

void LogoScreen::openMainMenuScreen() {
    game.setScreen(std::make_unique<MainMenuScreen>(game));
}