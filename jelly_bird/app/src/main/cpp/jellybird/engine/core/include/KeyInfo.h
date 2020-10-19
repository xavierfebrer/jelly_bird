#ifndef KEY_INFO_H
#define KEY_INFO_H

class KeyInfo {
public:
    bool pressed;

    KeyInfo(bool pressed = false);
    virtual ~KeyInfo();

    void set(bool pressed);

    KeyInfo & operator=(const KeyInfo & other) {
        pressed = other.pressed;
        return *this;
    }
};

#endif