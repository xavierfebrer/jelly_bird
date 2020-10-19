#include "../../include/AndroidInput.h"

AndroidInput::AndroidInput(android_app * app) : Input(), app(app) {
}

AndroidInput::~AndroidInput() {
}

BaseComponentReadiness AndroidInput::isReady() {
    return isInitialized() ? BaseComponentReadiness::READY : BaseComponentReadiness::NOT_READY;
}

void AndroidInput::startUpdate(double deltaTime) {
    BaseComponent::startUpdate(deltaTime);
}

void AndroidInput::endUpdate(double deltaTime) {
    BaseComponent::endUpdate(deltaTime);
    prevPointers = pointers;
    prevKeyMap = keyMap;
}

bool AndroidInput::isCursorEnabled() {
    return false;
}

void AndroidInput::enableCursor(bool enable) {
}

bool AndroidInput::parseAndroidInput(android_app * app, AInputEvent * event) {
    if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY) {
        if(AKeyEvent_getKeyCode(event) == AKEYCODE_BACK) {
            return true; // <-- prevent default handler
        }
    } else if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        auto source = AInputEvent_getSource(event);
        if(source == AINPUT_SOURCE_TOUCHSCREEN) {
            int32_t action = AKeyEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
            int32_t index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK);
                    //>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT; // TODO check
            if(index < Input::MAX_POINTERS) {
                if(action == AMOTION_EVENT_ACTION_DOWN) {
                    pointers[index].pressed = true;
                } else if(action == AMOTION_EVENT_ACTION_UP) {
                    pointers[index].pressed = false;
                }
                pointers[index].x = AMotionEvent_getX(event, index);
                pointers[index].y = AMotionEvent_getY(event, index);
            }
        }
    }
    return false;
}
