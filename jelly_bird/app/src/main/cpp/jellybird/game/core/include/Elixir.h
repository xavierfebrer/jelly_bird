#ifndef ELIXIR_H
#define ELIXIR_H

#include "Consumable.h"

class Elixir : public Consumable {
public:
    static const Vec2<> RENDER_SIZE;
    static const Vec2<> SIZE;
    static const long VALUE;
    static const double ENERGY;

    Elixir(GameWorld & gameWorld, double zOrder, double centerX, double centerY);
    virtual ~Elixir() override;

    virtual void create() override;
    virtual void collision(Entity * other) override;
};

#endif