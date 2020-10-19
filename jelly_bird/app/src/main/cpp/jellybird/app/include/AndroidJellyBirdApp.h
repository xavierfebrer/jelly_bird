#ifndef ANDROID_JELLY_BIRD_APP_H
#define ANDROID_JELLY_BIRD_APP_H

#include <android_native_app_glue.h>
#include "JellyBirdApp.h"
#include "../../game/core_android/include/AndroidJellyBirdGame.h"

class AndroidJellyBirdApp : public JellyBirdApp<AndroidJellyBirdGame, GameAppState> {
public:
    struct android_app * app;

    AndroidJellyBirdApp(struct android_app * app,
                        GameAppState & initState);
    virtual ~AndroidJellyBirdApp() override;

    virtual void init() override;
    virtual void resume() override;
    virtual void loop() override;
    virtual void pause() override;
    virtual void destroy() override;
    // from game/engine/...
    virtual void exit() override;

    // from OS
    virtual void onReceiveAppCmd(android_app * app, int32_t cmd);
    virtual bool onReceiveInputEvent(android_app * app, AInputEvent * event);

protected:
    virtual void onLoadEngine();
    virtual void onUnLoadEngine();
    virtual void onInitWindow();
    virtual void onTermWindow();
};


#endif
