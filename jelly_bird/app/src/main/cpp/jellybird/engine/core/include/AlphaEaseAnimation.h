#ifndef ALPHA_EASE_ANIMATION_H
#define ALPHA_EASE_ANIMATION_H

#include "AbsEaseAnimation.h"

class AlphaEaseAnimation : public AbsEaseAnimation {
private:
	const double start;
	const double end;
	double current;
	double percentCurrentDuration;
	std::unique_ptr<Ease> ease;
protected:
	virtual void updateCurrent() override;
	virtual void startEvent() override;
	virtual void updateEvent() override;
	virtual void endEvent() override;
public:
	AlphaEaseAnimation(double start, double end, double startDelay, double duration, std::unique_ptr<Ease> ease);
	virtual ~AlphaEaseAnimation();

	double getStart();
	double getCurrent();
	double getEnd();
};

#endif