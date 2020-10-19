#ifndef MOVE_EASE_ANIMATION_H
#define MOVE_EASE_ANIMATION_H

#include "AbsEaseAnimation.h"

class MoveEaseAnimation : public AbsEaseAnimation {
private:
	const Vec2<> start;
	const Vec2<> end;
	Vec2<> current;
	double percentCurrentDuration;
	std::unique_ptr<Ease> ease;
protected:
	virtual void updateCurrent() override;
	virtual void startEvent() override;
	virtual void updateEvent() override;
	virtual void endEvent() override;
public:
	MoveEaseAnimation(const Vec2<> & start, const Vec2<> & end, double startDelay, double duration, std::unique_ptr<Ease> ease);
	virtual ~MoveEaseAnimation();

	const Vec2<>& getStart();
	const Vec2<>& getCurrent();
	const Vec2<>& getEnd();
};

#endif