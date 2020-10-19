#include "../../../../include/Padding.h"
#include "../../../../include/Util.h"

const double Padding::MIN = 0;
const double Padding::MAX = 1;

Padding::Padding(const Padding & padding) : Padding(padding.h, padding.v) {
}

Padding::Padding(double h, double v) {
    setH(h);
    setV(v);
}

Padding::~Padding() {
}

double Padding::getV() {
    return v;
}

void Padding::setV(double v) {
    this->v = Util::minMax(v, Padding::MIN,
                                         Padding::MAX);
}

double Padding::getH() {
    return h;
}

void Padding::setH(double h) {
    this->h = Util::minMax(h, Padding::MIN,
                                           Padding::MAX);
}
