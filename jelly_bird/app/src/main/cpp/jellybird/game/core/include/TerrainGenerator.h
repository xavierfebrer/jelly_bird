#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include "Entity.h"

class Wall;

class TerrainGenerator : public Entity {
public:
    static const double MAX_DISTANCE_BETWEEN_ELIXIR;
    static const double MAX_DISTANCE_BETWEEN_CHERRY;

    double zOrderWall;
    double bottomY;
    double topY;
    double horizontalReach;
    double startX;
    double parsedX;
    double lastWallX;
    double lastElixirX;
    double lastCherryX;
    double minDistanceBetweenWalls;
    double offsetBetweenWalls;
    double minHoleSize;
    double offsetHoleSize;
    double topBottomPadding;
    bool imparFloor;

    TerrainGenerator(GameWorld & gameWorld, double zOrder, double zOrderWall, double bottomY, double topY,
                     double horizontalReach, double startX);
    virtual ~TerrainGenerator() override;

    virtual void create() override;
    virtual void resume() override;
    virtual void pause() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void collision(Entity * other) override;

    virtual void clear();
    std::shared_ptr<Wall> addWall(double x, double y);
    void setDistancePercent(float percent);
    void setHolePercent(float percent);
    void setCoinPercent(float percent);
protected:
    float distancePercent;
    float holePercent;
    float coinPercent;

    void resetValues();
    void parseRemaining();
    void maybeAddCoin();
    void maybeAddEnergy();
    double getDistanceBetweenWalls();
    double getHoleSize();
    double getCoinPercent();
};

#endif