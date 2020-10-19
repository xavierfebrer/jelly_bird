#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "BaseScreen.h"
#include "MainMenuScreen.h"
#include "EndScreen.h"
#include "GameWorld.h"

class GameScreen : public BaseScreen {
public:
    static const double TIME_AFTER_CRASH_TIME;

    GameScreen(JellyBirdGame & game, int worldIndex, int levelIndex);
    virtual ~GameScreen() override;

    virtual void create() override;
    virtual void resize(double width, double height) override;
    virtual void resume() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void pause() override;
protected:
    GameWorld gameWorld;
    int worldIndex;
    int levelIndex;
    double timeAfterCrash;

    virtual void initViews() override;
    virtual void goBack();
};

#endif