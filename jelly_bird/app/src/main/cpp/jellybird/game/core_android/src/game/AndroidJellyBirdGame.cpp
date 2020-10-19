#include "../../include/AndroidJellyBirdGame.h"
#include "../../include/AndroidLogoAssets.h"
#include "../../include/AndroidMenuAssets.h"
#include "../../include/AndroidGameAssets.h"

AndroidJellyBirdGame::AndroidJellyBirdGame(android_app* app) : JellyBirdGame(
        std::shared_ptr<AndroidLogoAssets>(new AndroidLogoAssets(app)),
        std::shared_ptr<AndroidMenuAssets>(new AndroidMenuAssets(app)),
        std::shared_ptr<AndroidGameAssets>(new AndroidGameAssets(app))), app(app) {
}

AndroidJellyBirdGame::~AndroidJellyBirdGame() {
}

void AndroidJellyBirdGame::exit() {
    ANativeActivity_finish(app->activity);
}