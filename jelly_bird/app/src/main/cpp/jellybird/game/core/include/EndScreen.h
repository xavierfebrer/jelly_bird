#ifndef END_SCREEN_H
#define END_SCREEN_H

#include "BaseScreen.h"
#include "MainMenuScreen.h"

class EndScreen : public BaseScreen {
public:
    EndScreen(JellyBirdGame & game, bool win);
    virtual ~EndScreen() override;

    virtual void create() override;
    virtual void resume() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void pause() override;
protected:
    virtual void initViews() override;
private:
    bool win;
    void openMainMenuScreen();
};

#endif