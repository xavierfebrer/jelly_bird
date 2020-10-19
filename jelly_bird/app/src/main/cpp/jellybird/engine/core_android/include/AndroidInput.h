#ifndef ANDROIDINPUT_H
#define ANDROIDINPUT_H

#include "../../core/include/Input.h"
#include <android_native_app_glue.h>
#include <android/sensor.h>
#include <android/log.h>

class AndroidInput : public Input {
public:
    android_app* app;

    AndroidInput(android_app* app);
    virtual ~AndroidInput() override;

    virtual BaseComponentReadiness isReady() override;

    virtual void startUpdate(double deltaTime) override;
    virtual void endUpdate(double deltaTime) override;
    virtual bool isCursorEnabled() override;
    virtual void enableCursor(bool enable) override;

    virtual bool parseAndroidInput(android_app * app, AInputEvent * event);
};

#endif