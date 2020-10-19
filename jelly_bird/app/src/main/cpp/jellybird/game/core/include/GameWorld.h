#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "../../../engine/core/include/BaseInclude.h"
#include "../../../engine/core/include/Game.h"
#include "../../../engine/core/include/CollisionUtil.h"
#include "../../../engine/core/include/Camera.h"
#include "../../../engine/core/include/Texture2DShader.h"
#include "Constants.h"
#include "JellyBirdGame.h"

class Entity;

class Bird;

class TerrainGenerator;

class Obstacle;

class Background;

class GameWorld {
public:
    static const Vec2<double> DEFAULT_GRAVITY;

    JellyBirdGame & game;
    Camera camera;
    Vec2<double> gravity;
    bool birdCrash;
    Texture2DShader * shader;
    std::shared_ptr<Background> bg;
    std::shared_ptr<Bird> bird;
    std::shared_ptr<TerrainGenerator> terrainGenerator;

    GameWorld(JellyBirdGame & game);
    virtual ~GameWorld();

    virtual void init();
    virtual void setupCamera();
    virtual void resume();
    virtual void pause();
    virtual void update(double deltaTime);
    virtual void render(double deltaTime);
    virtual int addEntity(const std::shared_ptr<Entity> & entity);
    virtual int addEntities(const std::vector<std::shared_ptr<Entity>> & entities);
    virtual int removeEntity(const std::shared_ptr<Entity> & entity);
    virtual int removeEntities(const std::vector<std::shared_ptr<Entity>> & entities);
protected:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Entity>> entitiesToAdd;

    virtual int addRemainingEntitiesToAdd();
    virtual void sortZOrder();
    virtual void updateEntities(double deltaTime);
    virtual void updateCollisions(double deltaTime);
    virtual bool checkRemoveFlagAndRemove(const std::shared_ptr<Entity> & entity);
};


#endif