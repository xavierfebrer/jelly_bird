#include "../../../../include/MainMenuScreen.h"
#include "../../../../../../engine/core/include/Hack3dEngine.h"

MainMenuScreen::MainMenuScreen(JellyBirdGame & game) : BaseScreen(game) {
}

MainMenuScreen::~MainMenuScreen() {
}

void MainMenuScreen::create() {
    BaseScreen::create();
}

void MainMenuScreen::initViews() {
    shader = game.menuAssets->shScene.get();
    Vec2<float> viewPort = camera.getViewPort();
    Rect<> viewSize;

    viewSize.set(-(16 * 2) * Constants::PIXEL_SIZE_W_UNIT, (16 * 1) * Constants::PIXEL_SIZE_W_UNIT,
                 (16 * 4) * Constants::PIXEL_SIZE_W_UNIT, (16 * 4) * Constants::PIXEL_SIZE_W_UNIT);
    auto btnMainLogo = std::make_shared<Button<JellyBirdGame>>(game, viewSize, Padding(),
                                                           *game.menuAssets->qTRButton, nullptr,
                                                           nullptr, nullptr,
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsMainLogo,
                                                                   0.05),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsMainLogo,
                                                                   0.0125),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsMainLogo,
                                                                   0.1));
    viewManager.addView(btnMainLogo);

    double speedAnimSlow = 0.46125;
    double speedAnimFast = speedAnimSlow / 4.0;
    viewSize.set(-(16 * 2) * Constants::PIXEL_SIZE_W_UNIT, -(16 * 4) * Constants::PIXEL_SIZE_W_UNIT,
                 (16 * 4) * Constants::PIXEL_SIZE_W_UNIT, (16 * 2) * Constants::PIXEL_SIZE_W_UNIT);
    auto btnPlay = std::make_shared<Button<JellyBirdGame>>(game, viewSize, Padding(0.75, 0.50),
                                                           *game.menuAssets->qTRButton,
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsPlayIdle,
                                                                   speedAnimSlow, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsPlayPressed,
                                                                   speedAnimFast, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsPlayDisabled,
                                                                   speedAnimSlow, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsButton4x2Idle,
                                                                   speedAnimSlow, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsButton4x2Pressed,
                                                                   speedAnimFast, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsButton4x2Disabled,
                                                                   speedAnimSlow, true));
    btnPlay->setOnReleaseClickListener([&](const Button<JellyBirdGame> &) { openGameScreen(); });
    viewManager.addView(btnPlay);

    viewSize.set((16 * 2.5) * Constants::PIXEL_SIZE_W_UNIT, -(16 * 8) * Constants::PIXEL_SIZE_W_UNIT,
                 (16 * 1.5) * Constants::PIXEL_SIZE_W_UNIT, (16 * 1.5) * Constants::PIXEL_SIZE_W_UNIT);
    auto btnSettings = std::make_shared<Button<JellyBirdGame>>(game, viewSize, Padding(1.0/3.0, 1.0/3.0),
                                                               *game.menuAssets->qTRButton,
                                                               Animation<TextureRegion2D>::create(
                                                                       game.menuAssets
                                                                               ->tRsSettingsIdle,
                                                                       speedAnimSlow * 2.0, true),
                                                               Animation<TextureRegion2D>::create(
                                                                       game.menuAssets
                                                                               ->tRsSettingsPressed,
                                                                       speedAnimFast * 2.0, true),
                                                               Animation<TextureRegion2D>::create(
                                                                       game.menuAssets
                                                                               ->tRsSettingsDisabled,
                                                                       speedAnimSlow * 2.0, true),
                                                               Animation<TextureRegion2D>::create(
                                                                       game.menuAssets
                                                                               ->tRsButton1x1_5Idle,
                                                                       speedAnimSlow * 2.0, true),
                                                               Animation<TextureRegion2D>::create(
                                                                       game.menuAssets
                                                                               ->tRsButton1x1_5Pressed,
                                                                       speedAnimFast * 2.0, true),
                                                               Animation<TextureRegion2D>::create(
                                                                       game.menuAssets
                                                                               ->tRsButton1x1_5Disabled,
                                                                       speedAnimSlow * 2.0, true));
    btnSettings->setOnReleaseClickListener([&](const Button<JellyBirdGame> &) { openSettingsScreen(); });
    viewManager.addView(btnSettings);

    viewSize.set(-(16 * 4.0) * Constants::PIXEL_SIZE_W_UNIT, -(16 * 8) * Constants::PIXEL_SIZE_W_UNIT,
                 (16 * 1.5) * Constants::PIXEL_SIZE_W_UNIT, (16 * 1.5) * Constants::PIXEL_SIZE_W_UNIT);
    auto btnExit = std::make_shared<Button<JellyBirdGame>>(game, viewSize, Padding(1.0/3.0, 1.0/3.0),
                                                               *game.menuAssets->qTRButton,
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsExitIdle,
                                                                   speedAnimSlow, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsExitPressed,
                                                                   speedAnimFast, true),
                                                           Animation<TextureRegion2D>::create(
                                                                   game.menuAssets
                                                                           ->tRsExitDisabled,
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
    btnExit->setOnReleaseClickListener([&](const Button<JellyBirdGame> &) { exitGame(); });
    viewManager.addView(btnExit);
}

void MainMenuScreen::resume() {
    game.menuAssets->load();
    BaseScreen::resume();
    game.menuAssets->mMenu->play();
    game.menuAssets->mMenu->setVolume(0.08f);
}

void MainMenuScreen::update(double deltaTime) {
    BaseScreen::update(deltaTime);
}

void MainMenuScreen::render(double deltaTime) {
    Hack3dEngine::get().graphics().clearScreen(1.0f, 0.1f, 0.1f, 0.1f);
    BaseScreen::render(deltaTime);
}

void MainMenuScreen::pause() {
    BaseScreen::pause();
    game.menuAssets->unLoad();
}

void MainMenuScreen::openGameScreen() {
    game.setScreen(std::make_unique<GameScreen>(game, 1, 1));
}

void MainMenuScreen::openSettingsScreen() {
}

void MainMenuScreen::exitGame() {
    game.exit();
}
