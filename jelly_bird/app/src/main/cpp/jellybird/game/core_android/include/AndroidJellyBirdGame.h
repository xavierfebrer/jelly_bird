#ifndef ANDROID_JELLY_BIRD_GAME_H
#define ANDROID_JELLY_BIRD_GAME_H

#include "../../core/include/JellyBirdGame.h"
#include <android_native_app_glue.h>

class AndroidJellyBirdGame : public JellyBirdGame {
public:
    android_app* app;

    AndroidJellyBirdGame(android_app* app);
    virtual ~AndroidJellyBirdGame() override;

    virtual void exit() override;
};

#endif