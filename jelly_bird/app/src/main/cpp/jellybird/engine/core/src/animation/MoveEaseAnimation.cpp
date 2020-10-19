#include "../../include/MoveEaseAnimation.h"

MoveEaseAnimation::MoveEaseAnimation(const Vec2<> & start, const Vec2<> & end, double startDelay, double duration, std::unique_ptr<Ease> ease)
	: AbsEaseAnimation(startDelay, duration), start(start), end(end), current(start), ease(std::move(ease)) {
}

MoveEaseAnimation::~MoveEaseAnimation() {
}

void MoveEaseAnimation::updateCurrent() {
	percentCurrentDuration = currentDuration / duration;
	current.x = ease->update(start.x, end.x, percentCurrentDuration);
	current.y = ease->update(start.y, end.y, percentCurrentDuration);
}

void MoveEaseAnimation::startEvent() {
}

void MoveEaseAnimation::updateEvent() {
}

void MoveEaseAnimation::endEvent() {
}

const Vec2<> & MoveEaseAnimation::getStart() {
	return start;
}

const Vec2<> & MoveEaseAnimation::getCurrent() {
	return current;
}

const Vec2<> & MoveEaseAnimation::getEnd() {
	return end;
}