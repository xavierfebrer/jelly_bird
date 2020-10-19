#include "../../include/AlphaEaseAnimation.h"

AlphaEaseAnimation::AlphaEaseAnimation(double start, double end, double startDelay, double duration, std::unique_ptr<Ease> ease)
	: AbsEaseAnimation(startDelay, duration), start(start), end(end), current(start), ease(std::move(ease)){
}

AlphaEaseAnimation::~AlphaEaseAnimation() {
}

void AlphaEaseAnimation::updateCurrent() {
	percentCurrentDuration = currentDuration / duration;
	current = ease->update(start, end, percentCurrentDuration);
}

void AlphaEaseAnimation::startEvent() {
}

void AlphaEaseAnimation::updateEvent() {
}

void AlphaEaseAnimation::endEvent() {
}

double AlphaEaseAnimation::getStart() {
	return start;
}

double AlphaEaseAnimation::getCurrent() {
	return current;
}

double AlphaEaseAnimation::getEnd() {
	return end;
}