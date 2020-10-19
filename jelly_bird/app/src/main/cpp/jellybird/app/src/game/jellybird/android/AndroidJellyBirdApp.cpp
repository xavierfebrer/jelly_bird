#include "../../../../include/AndroidJellyBirdApp.h"
#include "../../../../../engine/core_android/include/AndroidHack3dEngine.h"
#include "../../../../../engine/core_android/include/AndroidUtil.h"

AndroidJellyBirdApp::AndroidJellyBirdApp(struct android_app * app, GameAppState & initState)
        : JellyBirdApp(std::make_unique<AndroidJellyBirdGame>(app), initState), app(app) {
    AndroidHack3dEngine::get().app = app;
}

AndroidJellyBirdApp::~AndroidJellyBirdApp() {
}

void AndroidJellyBirdApp::init() {
    if(state == GameAppState::None) {
        state = GameAppState::Initialized;
        game->create();
    }
}

void AndroidJellyBirdApp::resume() {
    if(state != GameAppState::Destroyed && state != GameAppState::Resumed) {
        state = GameAppState::Resumed;
        game->resume();
        Hack3dEngine::get().setRenderEnabled(true);
    }
}

void AndroidJellyBirdApp::loop() {
    if(state != GameAppState::Destroyed &&
       (state == GameAppState::Looping || state == GameAppState::Resumed)) {
        state = GameAppState::Looping;
        game->loop();
    }
}

void AndroidJellyBirdApp::pause() {
    if(state != GameAppState::Destroyed && state != GameAppState::Paused) {
        state = GameAppState::Paused;
        Hack3dEngine::get().setRenderEnabled(false);
        game->pause();
    }
}

void AndroidJellyBirdApp::destroy() {
    if(state != GameAppState::Destroyed) {
        state = GameAppState::Destroyed;
        game.reset();
    }
}

void AndroidJellyBirdApp::onReceiveAppCmd(android_app * app, int32_t cmd) {
    switch(cmd) {
        case APP_CMD_INPUT_CHANGED:
            break;
        case APP_CMD_INIT_WINDOW:
            onInitWindow();
            break;
        case APP_CMD_TERM_WINDOW:
            onTermWindow();
            break;
        case APP_CMD_WINDOW_RESIZED:
            break;
        case APP_CMD_WINDOW_REDRAW_NEEDED:
            break;
        case APP_CMD_CONTENT_RECT_CHANGED:
            break;
        case APP_CMD_GAINED_FOCUS:
            break;
        case APP_CMD_LOST_FOCUS:
            break;
        case APP_CMD_CONFIG_CHANGED:
            break;
        case APP_CMD_LOW_MEMORY:
            break;
        case APP_CMD_START:
            break;
        case APP_CMD_RESUME:
            break;
        case APP_CMD_SAVE_STATE:
            break;
        case APP_CMD_PAUSE:
            break;
        case APP_CMD_STOP:
            break;
        case APP_CMD_DESTROY:
            destroy();
            break;
        default:
            break;
    }
}

bool AndroidJellyBirdApp::onReceiveInputEvent(android_app * app, AInputEvent * event) {
    AndroidHack3dEngine & engine = AndroidHack3dEngine::get();
    AndroidInput & input = engine.input();
    return input.parseAndroidInput(app, event);
}

void AndroidJellyBirdApp::exit() {
    ANativeActivity_finish(app->activity);
}

void AndroidJellyBirdApp::onLoadEngine() {
    if(AndroidHack3dEngine::get().graphics().onWindowInit(app->window)) {
        AndroidOpenSLESAudio & audioInit = AndroidHack3dEngine::get().audio();
        bool audioLoaded = audioInit.load();
        if(!audioLoaded) {
            exit();
            return;
        }
    } else {
        exit();
        return;
    }
}

void AndroidJellyBirdApp::onUnLoadEngine() {
    if(AndroidHack3dEngine::get().graphics().onWindowTerm()) {
        AndroidOpenSLESAudio & audioTerm = AndroidHack3dEngine::get().audio();
        bool audioUnLoaded = audioTerm.unLoad();
        if(!audioUnLoaded) {
            exit();
            return;
        }
    } else {
        exit();
        return;
    }
}


void AndroidJellyBirdApp::onInitWindow() {
    onLoadEngine();
    resume();
}

void AndroidJellyBirdApp::onTermWindow() {
    pause();
    onUnLoadEngine();
}