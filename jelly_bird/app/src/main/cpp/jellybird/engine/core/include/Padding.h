#ifndef PADDING_H
#define PADDING_H

#include "BaseInclude.h"

class Padding {
public:
    static const double MIN;
    static const double MAX;

    Padding(const Padding & padding);
    Padding(double h = Padding::MIN, double v = Padding::MIN);
    virtual ~Padding();

    double getV();
    void setV(double v);
    double getH();
    void setH(double h);
protected:
    double v;
    double h;
};

#endif