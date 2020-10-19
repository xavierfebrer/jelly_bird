#include "../../../include/LinearEase.h"

LinearEase::LinearEase() : Ease() {
}

LinearEase::~LinearEase() {
}

double LinearEase::update(double startValue, double endValue, double timePercent, const EaseSlow & easeSlow) const {
	if (startValue < endValue) {
		return startValue + ((endValue - startValue) * timePercent);
	} else {
		return startValue - ((startValue - endValue) * timePercent);
	}
}