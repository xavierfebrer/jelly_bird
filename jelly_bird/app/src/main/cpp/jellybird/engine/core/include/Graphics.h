#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "BaseComponent.h"
#include "Color.h"

class Graphics : public BaseComponent<> {
public:
    Graphics();
    virtual ~Graphics() override;

    virtual void onResizeEvent() = 0;
    virtual void startRender(double deltaTime) = 0;
    virtual void clearScreen(float a, float r, float g, float b) = 0;
    virtual void clearScreen(const Color & color) = 0;
    virtual void endRender(double deltaTime) = 0;
    virtual Vec2<int> getWindowSize() = 0;
};

#endif