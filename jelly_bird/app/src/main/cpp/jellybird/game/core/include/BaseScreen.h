#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include "../../../engine/core/include/Screen.h"
#include "../../../engine/core/include/ImageView.h"
#include "../../../engine/core/include/Button.h"

class JellyBirdGame;

class BaseScreen : public Screen<JellyBirdGame> {
public:
    BaseScreen(JellyBirdGame & game);
    virtual ~BaseScreen() override;

    virtual void create() override;
    virtual void resize(double width, double height) override;
    virtual void resume() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void pause() override;
protected:
    Camera camera;
    Texture2DShader * shader = nullptr;

    virtual void initViews() = 0;
    virtual void setupCamera();
};

#endif