#ifndef EASE_ANIMATION_H
#define EASE_ANIMATION_H

#include "BaseInclude.h"
#include "Ease.h"
#include "Vec2.h"

class EaseAnimation {
public:
    virtual void update(double deltaTime) = 0;
};

#endif