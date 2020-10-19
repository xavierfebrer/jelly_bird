#ifndef LOGO_SCREEN_H
#define LOGO_SCREEN_H

#include "BaseScreen.h"
#include "MainMenuScreen.h"

class LogoScreen : public BaseScreen {
public:
    LogoScreen(JellyBirdGame & game);
    virtual ~LogoScreen() override;

    virtual void create() override;
    virtual void resume() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void pause() override;
protected:
    virtual void initViews() override;
private:
    const double TIME_PER_LOGO = 0.0001;//2.0;
    const int NUM_LOGOS = 2;
    const double TARGET_TOTAL_TIME = TIME_PER_LOGO * NUM_LOGOS;
    double totalTime;

    void openMainMenuScreen();
};

#endif