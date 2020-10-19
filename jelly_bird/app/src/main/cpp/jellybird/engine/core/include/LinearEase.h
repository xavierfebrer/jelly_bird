#ifndef LINEAR_EASE_H
#define LINEAR_EASE_H

#include "Ease.h"

class LinearEase : public Ease {
public:
	LinearEase();
	virtual ~LinearEase();

	virtual double update(double startValue, double endValue, double timePercent, const EaseSlow & easeSlow = EaseSlow::START_END) const override;
};

#endif