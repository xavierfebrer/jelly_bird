#include "../../include/Input.h"

Input::Input() : BaseComponent() {
    for(int i = 0; i < MAX_POINTERS; i++) {
        prevPointers.push_back(PointerInfo());
        pointers.push_back(PointerInfo());
    }
}

Input::~Input() {
}

bool Input::isPrevPointerPressed(int pointerIndex) {
    return exists(prevPointers, pointerIndex) ? prevPointers[pointerIndex].pressed : false;
}

bool Input::isPointerPressed(int pointerIndex) {
    return exists(pointers, pointerIndex) ? pointers[pointerIndex].pressed : false;
}

bool Input::isPointerJustPressed(int pointerIndex) {
    return exists(prevPointers, pointerIndex) && exists(pointers, pointerIndex) ?
           !prevPointers[pointerIndex].pressed && pointers[pointerIndex].pressed : false;
}

bool Input::isPointerJustReleased(int pointerIndex) {
    return exists(prevPointers, pointerIndex) && exists(pointers, pointerIndex) ?
           prevPointers[pointerIndex].pressed && !pointers[pointerIndex].pressed : false;
}

PointerInfo Input::getPrevPointerInfo(int pointerIndex) {
    return exists(prevPointers, pointerIndex) ? prevPointers[pointerIndex] : false;
}

PointerInfo Input::getPointerInfo(int pointerIndex) {
    return exists(pointers, pointerIndex) ? pointers[pointerIndex] : false;
}

bool Input::isPrevKeyPressed(int keyIndex) {
    return exists(prevKeyMap, keyIndex) ? prevKeyMap[keyIndex].pressed : false;
}

bool Input::isKeyPressed(int keyIndex) {
    return exists(keyMap, keyIndex) ? keyMap[keyIndex].pressed : false;
}

bool Input::isKeyJustPressed(int keyIndex) {
    return exists(prevKeyMap, keyIndex) && exists(keyMap, keyIndex) ?
           !prevKeyMap[keyIndex].pressed && keyMap[keyIndex].pressed : false;
}

bool Input::isKeyJustReleased(int keyIndex) {
    return exists(prevKeyMap, keyIndex) && exists(keyMap, keyIndex) ?
           prevKeyMap[keyIndex].pressed && !keyMap[keyIndex].pressed : false;
}

std::map<int, KeyInfo> & Input::getPrevKeyInfo() {
    return prevKeyMap;
}

std::map<int, KeyInfo> & Input::getKeyInfo() {
    return keyMap;
}

bool Input::exists(const std::vector<PointerInfo> & pointers, int pointerIndex) {
    return pointerIndex >= 0 && pointerIndex < pointers.size();
}

bool Input::exists(const std::map<int, KeyInfo> & keys, int keyIndex) {
    return keys.find(keyIndex) != keys.end();
}

