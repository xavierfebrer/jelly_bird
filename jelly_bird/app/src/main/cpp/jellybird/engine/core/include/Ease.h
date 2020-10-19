#ifndef EASE_H
#define EASE_H

#include "BaseInclude.h"

enum class EaseSlow {
	START,
	END,
	START_END
};

class Ease {
public:
	Ease();
	virtual ~Ease();

	virtual double update(double startValue, double endValue, double timePercent, const EaseSlow & easeSlow = EaseSlow::START_END) const = 0;
};

#endif