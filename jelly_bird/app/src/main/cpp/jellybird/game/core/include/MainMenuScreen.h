#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "BaseScreen.h"
#include "GameScreen.h"

class MainMenuScreen : public BaseScreen {
public:
    MainMenuScreen(JellyBirdGame & game);
    virtual ~MainMenuScreen() override;

    virtual void create() override;
    virtual void resume() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void pause() override;
protected:
    virtual void initViews() override;
private:
    void openGameScreen();
    void openSettingsScreen();
    void exitGame();
};

#endif