#include "../../include/Color.h"

const double Color::MIN_COLOR = 0;
const double Color::MAX_COLOR = 1;

Color::Color(const Color & color) : Color(color.a, color.r, color.g, color.b) {
}

Color::Color(double a, double r, double g, double b) : a(
        Util::minMax(a, Color::MIN_COLOR, Color::MAX_COLOR)), r(Util::minMax(r, Color::MIN_COLOR,
                                                                             Color::MAX_COLOR)),
                                                       g(Util::minMax(g, Color::MIN_COLOR,
                                                                      Color::MAX_COLOR)),
                                                       b(Util::minMax(b, Color::MIN_COLOR,
                                                                      Color::MAX_COLOR)) {
}

Color::~Color() {
}
