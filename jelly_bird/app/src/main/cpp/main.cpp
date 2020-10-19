#include <initializer_list>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <jni.h>
#include <cerrno>
#include <cassert>
#include <cinttypes>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android_native_app_glue.h>

#include <dlfcn.h>
#include "jellybird/app/include/AndroidJellyBirdApp.h"

#define LOG_TAG "HACK2S"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "jelly-bird", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "jelly-bird", __VA_ARGS__))

static void handleCmd(struct android_app * app, int32_t cmd) {
    AndroidJellyBirdApp * jbAApp = (AndroidJellyBirdApp *) app->userData;
    /*switch(cmd) {
        case APP_CMD_INPUT_CHANGED:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_INPUT_CHANGED %d", cmd);
            break;
        case APP_CMD_INIT_WINDOW:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_INIT_WINDOW %d", cmd);
            break;
        case APP_CMD_TERM_WINDOW:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_TERM_WINDOW %d", cmd);
            break;
        case APP_CMD_WINDOW_RESIZED:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_WINDOW_RESIZED %d", cmd);
            break;
        case APP_CMD_WINDOW_REDRAW_NEEDED:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_WINDOW_REDRAW_NEEDED %d", cmd);
            break;
        case APP_CMD_CONTENT_RECT_CHANGED:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_CONTENT_RECT_CHANGED %d", cmd);
            break;
        case APP_CMD_GAINED_FOCUS:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_GAINED_FOCUS %d", cmd);
            break;
        case APP_CMD_LOST_FOCUS:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_LOST_FOCUS %d", cmd);
            break;
        case APP_CMD_CONFIG_CHANGED:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_CONFIG_CHANGED %d", cmd);
            break;
        case APP_CMD_LOW_MEMORY:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_LOW_MEMORY %d", cmd);
            break;
        case APP_CMD_START:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_START %d", cmd);
            break;
        case APP_CMD_RESUME:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_RESUME %d", cmd);
            break;
        case APP_CMD_SAVE_STATE:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_SAVE_STATE %d", cmd);
            break;
        case APP_CMD_PAUSE:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_PAUSE %d", cmd);
            break;
        case APP_CMD_STOP:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_STOP %d", cmd);
            break;
        case APP_CMD_DESTROY:
            LOGI(LOG_TAG
                         " -> App cmd APP_CMD_DESTROY %d", cmd);
            break;
        default:
            break;
    }*/
    jbAApp->onReceiveAppCmd(app, cmd);
}

static int32_t handleInput(struct android_app * app, AInputEvent * event) {
    AndroidJellyBirdApp * jbAApp = (AndroidJellyBirdApp *) app->userData;
    /*if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY) {
        LOGI(LOG_TAG
                     " --> Input event, key: action=%d flags=%d keyCode=%d scanCode=%d metaState=0x%x repeatCount=%d downTime=%"
                     PRIu64
                     " eventTime=%"
                     PRIu64, AKeyEvent_getAction(event), AKeyEvent_getFlags(event),
             AKeyEvent_getKeyCode(event), AKeyEvent_getScanCode(event),
             AKeyEvent_getMetaState(event), AKeyEvent_getRepeatCount(event),
             AKeyEvent_getDownTime(event), AKeyEvent_getEventTime(event));
    } else if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        unsigned int pointerId = 0;
        unsigned int axis = 0;
        unsigned int histotyIndex = 0;
        LOGI(LOG_TAG
                     " ---> Input event, motion: AA=%d AA=%d AA=%d AA=%d AA=%d BB=%"
                     PRIu64
                     " BB=%"
                     PRIu64
                     " CC=%.3f CC=%.3f CC=%.3f CC=%.3f DD=%zu EE=%d EE=%d CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f DD=%zu DD=%"
                     PRIu64
                     " CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f CC=%.3f",
             AMotionEvent_getAction(event), AMotionEvent_getFlags(event),
             AMotionEvent_getMetaState(event), AMotionEvent_getButtonState(event),
             AMotionEvent_getEdgeFlags(event), AMotionEvent_getDownTime(event),
             AMotionEvent_getEventTime(event), AMotionEvent_getXOffset(event),
             AMotionEvent_getYOffset(event), AMotionEvent_getXPrecision(event),
             AMotionEvent_getYPrecision(event), AMotionEvent_getPointerCount(event),
             AMotionEvent_getPointerId(event, pointerId),
             AMotionEvent_getToolType(event, pointerId), AMotionEvent_getRawX(event, pointerId),
             AMotionEvent_getRawY(event, pointerId), AMotionEvent_getX(event, pointerId),
             AMotionEvent_getY(event, pointerId), AMotionEvent_getPressure(event, pointerId),
             AMotionEvent_getSize(event, pointerId), AMotionEvent_getTouchMajor(event, pointerId),
             AMotionEvent_getTouchMinor(event, pointerId),
             AMotionEvent_getToolMajor(event, pointerId),
             AMotionEvent_getToolMinor(event, pointerId),
             AMotionEvent_getOrientation(event, pointerId),
             AMotionEvent_getAxisValue(event, axis, pointerId), AMotionEvent_getHistorySize(event),
             AMotionEvent_getHistoricalEventTime(event, histotyIndex),
             AMotionEvent_getHistoricalRawX(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalRawY(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalX(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalY(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalPressure(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalSize(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalTouchMajor(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalTouchMinor(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalToolMajor(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalToolMinor(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalOrientation(event, pointerId, histotyIndex),
             AMotionEvent_getHistoricalAxisValue(event, axis, pointerId, histotyIndex));
    }*/
    return jbAApp->onReceiveInputEvent(app, event) ? 1 : 0;
}

void android_main(struct android_app * app) {
    GameAppState gameAppState = GameAppState::None;
    AndroidJellyBirdApp * androidJellyBirdApp = new AndroidJellyBirdApp(app, gameAppState);
    auto jbAApp = std::shared_ptr<AndroidJellyBirdApp>(androidJellyBirdApp);

    // share instances to connect the app and the OS
    jbAApp->app = app;
    app->userData = jbAApp.get();

    // give OS events to the app
    app->onAppCmd = handleCmd;
    app->onInputEvent = handleInput;

    jbAApp->init();

    while(true) {
        int ident;
        int fD;
        int events;
        struct android_poll_source * source;

        while((ident = ALooper_pollAll(
                (jbAApp->state == GameAppState::Resumed || jbAApp->state == GameAppState::Looping)
                ? 0 : -1, &fD, &events, (void **) &source)) >= 0) {
            if(source != nullptr) {
                source->process(app, source);
            }
            if(app->destroyRequested != 0) {
                return;
            }
        }

        jbAApp->loop();
    }
}