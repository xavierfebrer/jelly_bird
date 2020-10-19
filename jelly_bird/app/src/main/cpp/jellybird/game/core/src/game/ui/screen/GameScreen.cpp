#include "../../../../include/GameScreen.h"
#include "../../../../../../engine/core/include/Hack3dEngine.h"
#include "../../../../include/Bird.h"

const double GameScreen::TIME_AFTER_CRASH_TIME = 3.0;

GameScreen::GameScreen(JellyBirdGame & game, int worldIndex, int levelIndex) : BaseScreen(game),
                                                                               gameWorld(GameWorld(
                                                                                       game)),
                                                                               worldIndex(
                                                                                       worldIndex),
                                                                               levelIndex(
                                                                                       levelIndex),
                                                                               timeAfterCrash(
                                                                                       TIME_AFTER_CRASH_TIME) {
}

GameScreen::~GameScreen() {
}

void GameScreen::create() {
    BaseScreen::create();
    gameWorld.init();
}

void GameScreen::initViews() {
    shader = game.menuAssets->shScene.get();
    Vec2<float> viewPort = camera.getViewPort();
    Rect<> viewSize;

    double speedAnimSlow = 1.0;
    double speedAnimFast = speedAnimSlow / 4.0;
    viewSize.set((viewPort.x * 0.5) - (16 * 1.5) * Constants::PIXEL_SIZE_W_UNIT,
                 (viewPort.y * 0.5) - (16 * 1.5) * Constants::PIXEL_SIZE_W_UNIT,
                 (16 * 1.5) * Constants::PIXEL_SIZE_W_UNIT, (16 * 1.5) * Constants::PIXEL_SIZE_W_UNIT);
    auto btnPause = std::make_shared<Button<JellyBirdGame>>(game, viewSize, Padding(1.0/3.0, 1.0/3.0),
                                                           *game.menuAssets->qTRButton,
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets->tRsPauseIdle,
                                                                   speedAnimSlow, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets->tRsPausePressed,
                                                                   speedAnimFast, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets->tRsPauseDisabled,
                                                                   speedAnimSlow, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsButton1x1_5Idle,
                                                                   speedAnimSlow, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsButton1x1_5Pressed,
                                                                   speedAnimFast, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsButton1x1_5Disabled,
                                                                   speedAnimSlow, true));
    btnPause->setOnReleaseClickListener([&](const Button<JellyBirdGame> &) {
        game.setScreen(std::make_unique<EndScreen>(game, false));
    });
    btnPause->setAlpha(0.25);
    viewManager.addView(btnPause);
}

void GameScreen::resize(double width, double height) {
    BaseScreen::resize(width, height);
    gameWorld.setupCamera();
}

void GameScreen::resume() {
    game.menuAssets->load();
    game.gameAssets->load();
    BaseScreen::resume();
    gameWorld.resume();
    game.gameAssets->mGame->play();
    game.gameAssets->mGame->setVolume(0.08f);
}

void GameScreen::update(double deltaTime) {
    BaseScreen::update(deltaTime);
    gameWorld.update(deltaTime);
    if(!gameWorld.bird->isAlive()) {
        if(timeAfterCrash <= 0) {
            game.setScreen(std::make_unique<EndScreen>(game, false));
        } else {
            if(Hack3dEngine::get().input().isPointerJustPressed(0) &&
               (timeAfterCrash / GameScreen::TIME_AFTER_CRASH_TIME) < 0.75) {
                timeAfterCrash = 0;
            } else {
                timeAfterCrash -= deltaTime;
            }
        }
    }
}

void GameScreen::render(double deltaTime) {
    Hack3dEngine::get().graphics().clearScreen(1.0f, 0.1f, 0.1f, 0.1f);
    gameWorld.render(deltaTime);
    BaseScreen::render(deltaTime);
}

void GameScreen::pause() {
    game.gameAssets->mGame->stop();
    gameWorld.pause();
    BaseScreen::pause();
    game.gameAssets->unLoad();
    game.menuAssets->unLoad();
}

void GameScreen::goBack() {
    game.setScreen(std::make_unique<MainMenuScreen>(game));
}
