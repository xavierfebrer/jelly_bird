#ifndef JELLY_BIRD_GAME_H
#define JELLY_BIRD_GAME_H

#include "../../../engine/core/include/Game.h"
#include "Constants.h"
#include "LogoAssets.h"
#include "MenuAssets.h"
#include "GameAssets.h"
#include "BaseScreen.h"

class JellyBirdGame : public Game<BaseScreen> {
public:
    std::shared_ptr<LogoAssets> logoAssets;
    std::shared_ptr<MenuAssets> menuAssets;
    std::shared_ptr<GameAssets> gameAssets;

    JellyBirdGame(const std::shared_ptr<LogoAssets> & logoAssets,
                  const std::shared_ptr<MenuAssets> & menuAssets,
                  const std::shared_ptr<GameAssets> & gameAssets);
    virtual ~JellyBirdGame() override;

    virtual bool create() override;
    virtual void resume() override;
    virtual void loop() override;
    virtual void pause() override;
    virtual void resize(double width, double height) override;
    virtual void setScreen(std::unique_ptr<BaseScreen> newScreen) override;
protected:
    bool initialized;
    bool running;
    long long currentTime = -1;
    long long prevTime = -1;
    std::unique_ptr<Screen<JellyBirdGame>> currentScreen;
    std::unique_ptr<Screen<JellyBirdGame>> newScreen;

    bool init();
    bool waitForReadyState();
    bool startGame();
    void update(double deltaTime);
    void render(double deltaTime);
    void checkNewScreen();

    void waitForTargetFPS();
};

#endif