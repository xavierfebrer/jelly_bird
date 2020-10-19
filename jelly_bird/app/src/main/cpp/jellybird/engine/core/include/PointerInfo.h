#ifndef POINTER_INFO_H
#define POINTER_INFO_H

class PointerInfo {
public:
    int x, y;
    bool pressed;
    double lastDownTime;
    double lastUpTime;

    PointerInfo(int x = 0, int y = 0, bool pressed = false, double lastDownTime = -1, double lastUpTime = -1);
    virtual ~PointerInfo();

    void set(int x, int y, bool pressed, double lastDownTime, double lastUpTime);
    void setPos(int x, int y);
    double diffLastDownTime(double time);
    double diffLastUpTime(double time);

    PointerInfo & operator=(const PointerInfo & other) {
        x = other.x;
        y = other.y;
        pressed = other.pressed;
        lastDownTime = other.lastDownTime;
        lastUpTime = other.lastUpTime;
        return *this;
    }

};

#endif