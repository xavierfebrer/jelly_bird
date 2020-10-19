#ifndef COLOR_H
#define COLOR_H

#include "BaseInclude.h"
#include "Util.h"

class Color {
public:
    static const double MIN_COLOR;
    static const double MAX_COLOR;

    double a, r, g, b;

    Color(const Color & color);
    Color(double a = MAX_COLOR, double r = MAX_COLOR, double g = MAX_COLOR, double b = MAX_COLOR);
    virtual ~Color();
};

#endif