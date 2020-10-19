#include "..\..\..\..\..\include\PointGoal.h"
#include "..\..\..\..\..\include\Bird.h"

const int PointGoal::DEFAULT_POINTS = 1;

PointGoal::PointGoal(GameWorld & gameWorld, double zOrder, double goalX, int points)
        : Entity(gameWorld, zOrder), goalX(goalX), points(points) {
}

PointGoal::~PointGoal() {
}

void PointGoal::create() {
}

void PointGoal::resume() {
}

void PointGoal::pause() {
}

void PointGoal::update(double deltaTime) {
    if (gameWorld.bird->pos.x >= goalX + (Wall::SIZE.x * 0.5) + (Bird::SIZE.x * 0.6)) {
        gameWorld.bird->addPoints(points, true);
        removed = true;
    }
}

void PointGoal::render(double deltaTime) {
}

void PointGoal::collision(Entity * other) {
}
