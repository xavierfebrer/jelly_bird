#ifndef BUTTON_H
#define BUTTON_H

#include "View.h"
#include "Padding.h"
#include "QuadTextureRegion2D.h"
#include "Animation.h"
#include "CollisionUtil.h"

enum class PressedState {
    NOT_PRESSED, PRESSED
};

enum class ButtonEvent {
    ON_PRESSED, ON_RELEASED, NONE
};

template<typename G>
class Button : public View<G> {
public:
    Button(G & game, const Rect<> & bounds, const Padding & padding,
           QuadTextureRegion2D & qTRButton,
           std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationIdle,
           std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationPressed,
           std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationDisabled,
           std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGIdle,
           std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGPressed,
           std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGDisabled);
    virtual ~Button() override;

    virtual void resume() override;
    virtual bool
    input(double deltaTime, const PointerEventInfo & pointerEventInfo, bool consumed) override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime, Camera & camera, Texture2DShader & shader) override;
    virtual void resize(double width, double height) override;
    virtual void pause() override;
    virtual void setEnabled(bool enabled) override;
    virtual void restartViewAnimations();
    virtual void setPadding(const Padding & padding);
    virtual const Padding & getPadding();
    virtual double getPaddingWidth();
    virtual double getPaddingHeight();
    virtual bool isPressed();
    virtual void
    setOnPressClickListener(const std::function<void(const Button<G> & view)> & listener);
    virtual void
    setOnReleaseClickListener(const std::function<void(const Button<G> & view)> & listener);
protected:
    Padding padding;
    QuadTextureRegion2D & qTRButton;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> currentAnimation;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> currentBGAnimation;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animIdle;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animPressed;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animDisabled;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animBGIdle;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animBGPressed;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animBGDisabled;
    PressedState prevPressedState;
    PressedState pressedState;
    ButtonEvent currentEvent;
    std::function<void(const Button<G> &)> listenerPress = [](const Button<G> & view) {};
    std::function<void(const Button<G> &)> listenerRelease = [](const Button<G> & view) {};
    /*
    std::function<void()> const & listener;
    std::function<int()> myFunction = []() { return 0; }
     */

    virtual bool updateInput(double deltaTime, const PointerEventInfo & pointerEventInfo);
    virtual ButtonEvent
    updateInputInternal(double deltaTime, const PointerEventInfo & pointerEventInfo);
    virtual void checkAndSetCurrentAnimation();
};

template<typename G>
Button<G>::Button(G & game, const Rect<> & bounds, const Padding & padding,
                  QuadTextureRegion2D & qTRButton,
                  std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationIdle,
                  std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationPressed,
                  std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationDisabled,
                  std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGIdle,
                  std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGPressed,
                  std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGDisabled)
        : View<G>(game, bounds), padding(padding), qTRButton(qTRButton),
          animIdle(std::move(animationIdle)), animPressed(std::move(animationPressed)),
          animDisabled(std::move(animationDisabled)), animBGIdle(std::move(animationBGIdle)),
          animBGPressed(std::move(animationBGPressed)),
          animBGDisabled(std::move(animationBGDisabled)) {
    prevPressedState = PressedState::NOT_PRESSED;
    pressedState = PressedState::NOT_PRESSED;
    setEnabled(true);
    currentAnimation = this->animIdle;
    currentBGAnimation = this->animBGIdle;
}

template<typename G>
Button<G>::~Button() {
}

template<typename G>
void Button<G>::resume() {
}

template<typename G>
bool Button<G>::input(double deltaTime, const PointerEventInfo & pointerEventInfo, bool consumed) {
    if(pointerEventInfo.pointerIndex == 0) {    // buttons only accept the first pointer
        if(!consumed) {
            return updateInput(deltaTime, pointerEventInfo);
        }
    }
    return consumed;
}

template<typename G>
bool Button<G>::updateInput(double deltaTime, const PointerEventInfo & pointerEventInfo) {
    if(this->isEnabled()) {
        currentEvent = updateInputInternal(deltaTime, pointerEventInfo);
        if(currentEvent != ButtonEvent::NONE) {
            if(currentEvent == ButtonEvent::ON_PRESSED) {
                if(currentAnimation) {
                    currentAnimation = animPressed;
                }
                if(currentBGAnimation) {
                    currentBGAnimation = animBGPressed;
                }
                listenerPress(*this);
            } else if(currentEvent == ButtonEvent::ON_RELEASED) {
                if(currentAnimation) {
                    currentAnimation = animIdle;
                }
                if(currentBGAnimation) {
                    currentBGAnimation = animBGIdle;
                }
                listenerRelease(*this);
            }
        }
    }
    return pressedState == PressedState::PRESSED;
}

template<typename G>
ButtonEvent
Button<G>::updateInputInternal(double deltaTime, const PointerEventInfo & pointerEventInfo) {
    prevPressedState = pressedState;
    currentEvent = ButtonEvent::NONE;
    if(prevPressedState == PressedState::NOT_PRESSED) {
        if(pointerEventInfo.pointerEvent != PointerEvent::IDLE &&
           pointerEventInfo.pointerEvent != PointerEvent::UP &&
           CollisionUtil<>::collision(pointerEventInfo.xViewCamera, pointerEventInfo.yViewCamera,
                                      this->bounds)) {
            pressedState = PressedState::PRESSED;
            currentEvent = ButtonEvent::ON_PRESSED;
        }
    } else if(prevPressedState == PressedState::PRESSED) {
        if(pointerEventInfo.pointerEvent != PointerEvent::IDLE &&
           pointerEventInfo.pointerEvent != PointerEvent::UP) {
            if(!CollisionUtil<>::collision(pointerEventInfo.xViewCamera,
                                           pointerEventInfo.yViewCamera, this->bounds)) {
                pressedState = PressedState::NOT_PRESSED;
            }
        } else {
            if(CollisionUtil<>::collision(pointerEventInfo.xViewCamera,
                                          pointerEventInfo.yViewCamera, this->bounds)) {
                currentEvent = ButtonEvent::ON_RELEASED;
            }
            pressedState = PressedState::NOT_PRESSED;
        }
    }
    return currentEvent;
}

template<typename G>
void Button<G>::update(double deltaTime) {
    View<G>::update(deltaTime);
    checkAndSetCurrentAnimation();
    if(currentAnimation) {
        currentAnimation->update(deltaTime);
    }
    if(currentBGAnimation) {
        currentBGAnimation->update(deltaTime);
    }
}

template<typename G>
void Button<G>::render(double deltaTime, Camera & camera, Texture2DShader & shader) {
    if(currentBGAnimation) {
        qTRButton.textureRegion2D = currentBGAnimation->getCurrentStep().getItem().get();
        qTRButton.render(shader, camera, this->bounds.x, this->bounds.y, -1, this->bounds.w,
                         this->bounds.h, 0.0, Vec2<>(1, 1), Vec2<>(0.5, 0.5), Color(this->getAlpha()));
    }
    if(currentAnimation) {
        qTRButton.textureRegion2D = currentAnimation->getCurrentStep().getItem().get();
        qTRButton.render(shader, camera,
                         this->bounds.x + (this->bounds.w * 0.5) * (this->padding.getH()),
                         this->bounds.y + (this->bounds.h * 0.5) * (this->padding.getV()), -1,
                         this->bounds.w * (1.0 - this->padding.getH()),
                         this->bounds.h * (1.0 - this->padding.getV()), 0.0, Vec2<>(1, 1),
                         Vec2<>(0.5, 0.5), Color(this->getAlpha()));
    }
}

template<typename G>
void Button<G>::resize(double width, double height) {
}

template<typename G>
void Button<G>::pause() {
}

template<typename G>
void Button<G>::setEnabled(bool enabled) {
    if(this->isEnabled() != enabled) {
        restartViewAnimations();
        checkAndSetCurrentAnimation();
    }
    View<G>::setEnabled(enabled);
    if(!this->isEnabled()) {
        prevPressedState = PressedState::NOT_PRESSED;
        pressedState = PressedState::NOT_PRESSED;
    }
}

template<typename G>
void Button<G>::restartViewAnimations() {
    if(animBGIdle) {
        animBGIdle->restart();
    }
    if(animBGPressed) {
        animBGPressed->restart();
    }
    if(animBGDisabled) {
        animBGDisabled->restart();
    }
    if(animIdle) {
        animIdle->restart();
    }
    if(animPressed) {
        animPressed->restart();
    }
    if(animDisabled) {
        animDisabled->restart();
    }
}

template<typename G>
void Button<G>::setPadding(const Padding & padding) {
    this->padding = padding;
}

template<typename G>
const Padding & Button<G>::getPadding() {
    return padding;
}

template<typename G>
double Button<G>::getPaddingWidth() {
    return this->bounds.w * padding.getH();
}

template<typename G>
double Button<G>::getPaddingHeight() {
    return this->bounds.h * padding.getV();
}

template<typename G>
bool Button<G>::isPressed() {
    return pressedState == PressedState::PRESSED && this->isEnabled();
}

template<typename G>
void Button<G>::checkAndSetCurrentAnimation() {
    if(this->isEnabled()) {
        if(prevPressedState != pressedState) {
            restartViewAnimations();
            if(pressedState == PressedState::NOT_PRESSED) {
                if(currentAnimation) {
                    currentAnimation = animIdle;
                }
                if(currentBGAnimation) {
                    currentBGAnimation = animBGIdle;
                }
            } else {
                if(currentAnimation) {
                    currentAnimation = animPressed;
                }
                if(currentBGAnimation) {
                    currentBGAnimation = animBGPressed;
                }
            }
        }
    } else {
        if(currentAnimation != animDisabled || currentBGAnimation != animBGDisabled) {
            restartViewAnimations();
            if(currentAnimation) {
                currentAnimation = animDisabled;
            }
            if(currentBGAnimation) {
                currentBGAnimation = animBGDisabled;
            }
        }
    }
}

template<typename G>
void Button<G>::setOnPressClickListener(const std::function<void(const Button<G> &)> & listener) {
    this->listenerPress = listener;
}

template<typename G>
void Button<G>::setOnReleaseClickListener(const std::function<void(const Button<G> &)> & listener) {
    this->listenerRelease = listener;
}

#endif