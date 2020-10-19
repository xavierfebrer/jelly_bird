#include "../../../../../include/Consumable.h"
#include "../../../../../include/GameAssets.h"
#include "../../../../../include/Bird.h"

const Vec2<double> Consumable::RENDER_SIZE = Vec2<double>(16 * Constants::PIXEL_SIZE_W_UNIT,
                                                       16 * Constants::PIXEL_SIZE_W_UNIT);
const Vec2<double> Consumable::SIZE = Vec2<double>(8 * Constants::PIXEL_SIZE_W_UNIT,
                                                8 * Constants::PIXEL_SIZE_W_UNIT);
const Color Consumable::DEFAULT_TINT = Color(1.0, 1.0, 1.0, 1.0);

Consumable::Consumable(GameWorld & gameWorld, double zOrder, double centerX, double centerY, double sizeX, double sizeY,
        double renderSizeX, double renderSizeY, long value, double energy) : Obstacle(
        gameWorld, zOrder, centerX, centerY, sizeX, sizeY, renderSizeX, renderSizeY, DEFAULT_TINT), value(value), energy(energy) {
}

Consumable::~Consumable() {
}

void Consumable::collision(Entity * other) {
    if (Bird * b = dynamic_cast<Bird*>(other)) {
        removed = true;
    }
}