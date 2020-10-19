#ifndef ANIMATION_H
#define ANIMATION_H

#include "BaseInclude.h"
#include "Vec2.h"
#include "AnimationStep.h"

template<typename R>
class Animation {
private:
    double deltaTimeLeft;
    int initialLoopsLeft;
    int loopsLeft;
    int currentStepIndex;
    std::vector<std::unique_ptr<AnimationStep<R>>> steps;
public:
    Animation(std::vector<std::unique_ptr<AnimationStep<R>>> steps, int loopTimes = -1);
    virtual ~Animation();

    void setLoopTimes(int loopTimes);
    const bool isInfinite() const;
    const int getLoopsLeft();
    void decreaseLoopsLeft();
    const bool hasEnded();
    void update(double deltaTime, double scale = 1.0);
    const bool nextCurrentStepIndex();
    void setSteps(std::vector<std::unique_ptr<AnimationStep<R>>> steps);
    void restart();
    void randomizeCurrentStep();
    AnimationStep<R> & getCurrentStep();
    const double getDuration() const;
    const double getTimeLeft() const;
    int getCurrentStepIndex();
    int getNumSteps();

    static std::unique_ptr<Animation<std::shared_ptr<R>>> create(std::shared_ptr<R> & item, double time = std::numeric_limits<double>::max());
    static std::unique_ptr<Animation<std::shared_ptr<R>>>
    create(std::vector<std::shared_ptr<R>> & items, double time = std::numeric_limits<double>::max(), bool randomizeIndex = false);
};

template<typename R>
Animation<R>::Animation(std::vector<std::unique_ptr<AnimationStep<R>>> steps, int loopTimes) {
    setSteps(std::move(steps));
    setLoopTimes(loopTimes);
}

template<typename R>
Animation<R>::~Animation() {
}

template<typename R>
void Animation<R>::setLoopTimes(int loopTimes) {
    if(loopTimes == 0) {
        throw "loopTimes must be negative (infinite loops) or greater than 0.";
    }
    initialLoopsLeft = loopTimes;
    loopsLeft = loopTimes;
}

template<typename R>
const bool Animation<R>::isInfinite() const {
    return initialLoopsLeft < 0;
}

template<typename R>
const int Animation<R>::getLoopsLeft() {
    return loopsLeft;
}

template<typename R>
void Animation<R>::decreaseLoopsLeft() {
    loopsLeft -= 1;
}

template<typename R>
const bool Animation<R>::hasEnded() {
    return loopsLeft == 0 && getCurrentStep().isFinished();
}

template<typename R>
void Animation<R>::update(double deltaTime, double scale) {
    deltaTimeLeft = getCurrentStep().update(deltaTime, scale);
    if(deltaTimeLeft > 0) {
        if(nextCurrentStepIndex()) {
            update(deltaTimeLeft);
        }
    }
}

template<typename R>
const bool Animation<R>::nextCurrentStepIndex() {
    if(currentStepIndex < steps.size() - 1) {
        currentStepIndex++;
    } else if(getLoopsLeft() == -1) {
        currentStepIndex = 0;
    } else if(getLoopsLeft() == 1) {
        decreaseLoopsLeft();
        return false;
    } else if(getLoopsLeft() > 0) {
        decreaseLoopsLeft();
        currentStepIndex = 0;
    } else {
        return false;
    }
    getCurrentStep().restart();
    return true;
}

template<typename R>
void Animation<R>::setSteps(std::vector<std::unique_ptr<AnimationStep<R>>> newSteps) {
    if(newSteps.empty()) { throw "steps parameter must not be null or empty."; }
    steps.clear();
    steps.swap(newSteps);
    restart();
}

template<typename R>
void Animation<R>::restart() {
    currentStepIndex = 0;
    loopsLeft = initialLoopsLeft;
    for(size_t i = 0; i < steps.size(); i++) {
        steps[i]->restart();
    }
}

template<typename R>
void Animation<R>::randomizeCurrentStep() {
    restart();
    currentStepIndex = Util::randInt(0, steps.size() - 1);
}

template<typename R>
AnimationStep<R> & Animation<R>::getCurrentStep() {
    return *steps[currentStepIndex];
}

template<typename R>
const double Animation<R>::getDuration() const {
    double duration = 0;
    for(size_t i = 0; i < steps.size(); i++) {
        duration += steps[i]->getTime();
    }
    if(initialLoopsLeft > 0) {
        duration *= initialLoopsLeft;
    }
    return duration;
}

template<typename R>
const double Animation<R>::getTimeLeft() const {
    double timeLeft = 0;
    for(size_t i = 0; i < steps.size(); i++) {
        timeLeft += steps[i]->getTimeLeft();
    }
    if(initialLoopsLeft > 0) {
        timeLeft *= initialLoopsLeft;
    }
    return timeLeft;
}

template<typename R>
int Animation<R>::getCurrentStepIndex() {
    return currentStepIndex;
}

template<typename R>
int Animation<R>::getNumSteps() {
    return steps.size();
}

template<typename R>
std::unique_ptr<Animation<std::shared_ptr<R>>> Animation<R>::create(std::shared_ptr<R> & item, double time) {
    return std::make_unique<Animation<std::shared_ptr<R>>>(
            AnimationStep<std::shared_ptr<R>>::createList(item, time));
}

template<typename R>
std::unique_ptr<Animation<std::shared_ptr<R>>> Animation<R>::create(std::vector<std::shared_ptr<R>> & items, double time, bool randomizeIndex) {
    auto animation = std::make_unique<Animation<std::shared_ptr<R>>>(
            AnimationStep<std::shared_ptr<R>>::createList(items, time));
    if(randomizeIndex){
        animation->randomizeCurrentStep();
    }
    return animation;
}


#endif