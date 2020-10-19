#include "../../../include/ExpEase.h"

ExpEase::ExpEase() : Ease() {
}

ExpEase::~ExpEase() {
}

double ExpEase::update(double startValue, double endValue, double timePercent,
                       const EaseSlow & easeSlow) const {
    if(easeSlow == EaseSlow::START || (easeSlow == EaseSlow::START_END && timePercent < 0.5)) {
        if(startValue < endValue) {
            return startValue + ((endValue - startValue) * (timePercent * timePercent));
        } else {
            return startValue - ((startValue - endValue) * (timePercent * timePercent));
        }
    } else {
        // TODO FIX
        if(startValue < endValue) {
            return startValue + ((endValue - startValue) * (timePercent * timePercent));
        } else {
            return startValue - ((startValue - endValue) * (timePercent * timePercent));
        }
    }
}