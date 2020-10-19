#include "../../../../include/EndScreen.h"
#include "../../../../../../engine/core/include/Hack3dEngine.h"

EndScreen::EndScreen(JellyBirdGame & game, bool win) : BaseScreen(game), win(win) {
}

EndScreen::~EndScreen() {
}

void EndScreen::create() {
    game.gameAssets->unLoad();
    //Hack3dEngine::get().assets().menu->load();
    BaseScreen::create();
    openMainMenuScreen();
}

void EndScreen::initViews() {
}

void EndScreen::resume() {
    BaseScreen::resume();
}

void EndScreen::update(double deltaTime) {
    BaseScreen::update(deltaTime);
}

void EndScreen::render(double deltaTime) {
    Hack3dEngine::get().graphics().clearScreen(1.0f, 0.1f, 0.1f, 0.1f);
    BaseScreen::render(deltaTime);
}

void EndScreen::pause() {
    BaseScreen::pause();
}

void EndScreen::openMainMenuScreen() {
    game.setScreen(std::make_unique<MainMenuScreen>(game));
}
