#ifndef INPUT_H
#define INPUT_H

#include "BaseInclude.h"

#include "BaseComponent.h"
#include "PointerInfo.h"
#include "KeyInfo.h"

class Input : public BaseComponent<> {
public:
    static const int MAX_POINTERS = 20;
    static const int KEY_BACK;
    static const int KEY_ESCAPE;
    static const int KEY_LEFT_ALT;
    static const int KEY_ENTER;

    Input();
    virtual ~Input() override;

    bool isPrevPointerPressed(int pointerIndex);
    bool isPointerPressed(int pointerIndex);
    bool isPointerJustPressed(int pointerIndex);
    bool isPointerJustReleased(int pointerIndex);
    PointerInfo getPrevPointerInfo(int pointerIndex);
    PointerInfo getPointerInfo(int pointerIndex);
    bool isPrevKeyPressed(int keyIndex);
    bool isKeyPressed(int keyIndex);
    bool isKeyJustPressed(int keyIndex);
    bool isKeyJustReleased(int keyIndex);
    std::map<int, KeyInfo> & getPrevKeyInfo();
    std::map<int, KeyInfo> & getKeyInfo();
    virtual bool isCursorEnabled() = 0;
    virtual void enableCursor(bool enable) = 0;
protected:
    std::vector<PointerInfo> prevPointers;
    std::vector<PointerInfo> pointers;
    std::map<int, KeyInfo> prevKeyMap;
    std::map<int, KeyInfo> keyMap;

    virtual bool exists(const std::vector<PointerInfo> & pointers, int pointerIndex);
    virtual bool exists(const std::map<int, KeyInfo> & keys, int keyIndex);
};

#endif