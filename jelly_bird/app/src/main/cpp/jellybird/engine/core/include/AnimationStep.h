#ifndef ANIMATION_STEP_H
#define ANIMATION_STEP_H

#include "BaseInclude.h"
#include "Vec2.h"
#include "TextureRegion2D.h"

template<typename R>
class AnimationStep {
private:
    double time;
    double currentTime;
    R & item;
public:
    AnimationStep(double time, R & item);
    virtual ~AnimationStep();

    const double update(double deltaTime, double scale = 1.0);
    void restart();
    const bool isFinished() const;
    void finish();
    const double getTime();
    const double getTimeLeft();
    void setTime(double time);
    R & getItem();

    static std::vector<std::unique_ptr<AnimationStep>>
    createList(R & item, double time = std::numeric_limits<double>::max());
    static std::vector<std::unique_ptr<AnimationStep>>
    createList(std::vector<R> & items, double time = std::numeric_limits<double>::max());
};

template<typename R>
AnimationStep<R>::AnimationStep(double time, R & item) : time(0), item(item) {
    setTime(time);
    currentTime = time;
    restart();
}

template<typename R>
AnimationStep<R>::~AnimationStep() {
}

template<typename R>
const double AnimationStep<R>::update(double deltaTime, double scale) {
    deltaTime *= scale;
    if(deltaTime <= currentTime) {
        currentTime -= deltaTime;
        return 0;
    } else {
        deltaTime = deltaTime - currentTime;
        currentTime = 0;
        return deltaTime;
    }
}

template<typename R>
void AnimationStep<R>::restart() {
    currentTime = time;
}

template<typename R>
const bool AnimationStep<R>::isFinished() const {
    return currentTime <= 0;
}

template<typename R>
void AnimationStep<R>::finish() {
    currentTime = 0;
}

template<typename R>
const double AnimationStep<R>::getTime() {
    return time;
}

template<typename R>
const double AnimationStep<R>::getTimeLeft() {
    return currentTime;
}

template<typename R>
void AnimationStep<R>::setTime(double time) {
    if(time <= 0) {
        throw "time parameter must be > 0.";
    }
    this->time = time;
}

template<typename R>
R & AnimationStep<R>::getItem() {
    return item;
}

template<typename R>
std::vector<std::unique_ptr<AnimationStep<R>>> AnimationStep<R>::createList(R & item, double time) {
    std::vector<std::unique_ptr<AnimationStep<R>>> steps;
    steps.push_back(std::make_unique<AnimationStep<R>>(time, item));
    return steps;
}

template<typename R>
std::vector<std::unique_ptr<AnimationStep<R>>>
AnimationStep<R>::createList(std::vector<R> & items, double time) {
    std::vector<std::unique_ptr<AnimationStep<R>>> steps;
    for (size_t i = 0; i < items.size(); ++i) {
        steps.push_back(std::make_unique<AnimationStep<R>>(time, items[i]));
    }
    return steps;
}

#endif