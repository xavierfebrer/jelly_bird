#include "../../include/PointerInfo.h"

PointerInfo::PointerInfo(int x, int y, bool pressed, double lastDownTime, double lastUpTime) : x(x),
                                                                                               y(y),
                                                                                               pressed(pressed),
                                                                                               lastDownTime(
                                                                                                       lastDownTime),
                                                                                               lastUpTime(
                                                                                                       lastUpTime) {
}

PointerInfo::~PointerInfo() {
}

void PointerInfo::set(int x, int y, bool pressed, double lastDownTime, double lastUpTime) {
    setPos(x, y);
    this->pressed = pressed;
    this->lastDownTime = lastDownTime;
    this->lastUpTime = lastUpTime;
}

void PointerInfo::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

double PointerInfo::diffLastDownTime(double time) {
    return time - lastDownTime;
}

double PointerInfo::diffLastUpTime(double time) {
    return time - lastUpTime;
}