#include "../../../../include/Entity.h"

const double Entity::DEFAULT_Z_ORDER = 0.0;

Entity::Entity(GameWorld & gameWorld, double zOrder) : zOrder(zOrder), removed(false),
                                                       gameWorld(gameWorld) {
}

Entity::~Entity() {
}