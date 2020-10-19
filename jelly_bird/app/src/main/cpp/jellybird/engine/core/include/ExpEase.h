#ifndef EXP_EASE_H
#define EXP_EASE_H

#include "Ease.h"

class ExpEase : public Ease {
public:
	ExpEase();
	virtual ~ExpEase();

	virtual double update(double startValue, double endValue, double timePercent, const EaseSlow & easeSlow = EaseSlow::START_END) const override;
};

#endif