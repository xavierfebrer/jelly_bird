#include "../../../include/GameWorld.h"
#include "../../../../../engine/core/include/Hack3dEngine.h"
#include "../../../include/Entity.h"
#include "../../../include/Bird.h"
#include "../../../include/Obstacle.h"
#include "../../../include/Consumable.h"
#include "../../../include/TerrainGenerator.h"
#include "../../../include/Background.h"
#include "../../../include/GameAssets.h"

const Vec2<double> GameWorld::DEFAULT_GRAVITY = Vec2<>(0.0, -9.8);

GameWorld::GameWorld(JellyBirdGame & game) : game(game), camera(Camera(CameraProjection::Orthogonal,
                                                                       Vec2<float>())),
                                             gravity(DEFAULT_GRAVITY), birdCrash(false) {
}

GameWorld::~GameWorld() {
}

void GameWorld::init() {
    shader = game.gameAssets->shScene.get();

    setupCamera();

    double startX = 0;
    double startXTerrain = startX - 5.5;
    double top = 14;
    double bottom = -8;
    double horizontalReach = 50;

    bg = std::shared_ptr<Background>(new Background(*this, -2));
    addEntity(bg);
    bg->setInitialOffset(Util::random(), Util::random());

    bird = std::shared_ptr<Bird>(new Bird(*this, -1.6, startX, bottom + ((top - bottom) * 0.75)));
    addEntity(bird);

    terrainGenerator = std::shared_ptr<TerrainGenerator>(
            new TerrainGenerator(*this, -1.1, -1.2, bottom, top, horizontalReach, startXTerrain));
    addEntity(terrainGenerator);
}

void GameWorld::resume() {
    for(auto & entity : entities) { entity->resume(); }
}

void GameWorld::pause() {
    for(auto & entity : entities) { entity->pause(); }
}

void GameWorld::update(double deltaTime) {
    addRemainingEntitiesToAdd();
    sortZOrder();
    updateEntities(deltaTime);
    updateCollisions(deltaTime);

    double difficulty = Util::minMax((bird->points / 200.0) + 0.025, 0.025, 1.0);
    terrainGenerator->setDistancePercent(1.0 - difficulty);
    terrainGenerator->setHolePercent(1.0 - difficulty);
    terrainGenerator->setCoinPercent(difficulty);

    //camera.setPosition(bird->pos.x + camera.getViewPort().x * 0.20, camera.getPosition().y, camera.getPosition().z);
    camera.setPosition(bird->pos.x + camera.getViewPort().x * 0.1, camera.getPosition().y,
                        camera.getPosition().z);
    camera.updateCameraVectors();
    bg->addInitialOffset(deltaTime * 0.0001, 0);
    bg->setOffset(camera.getPosition().x * 0.0005, 0);
}

void GameWorld::render(double deltaTime) {
    for(auto & entity : entities) { entity->render(deltaTime); }
}

int GameWorld::addEntity(const std::shared_ptr<Entity> & entity) {
    int countAdded = 0;
    if(entity) {
        entitiesToAdd.push_back(entity);
        ++countAdded;
    }
    return countAdded;
}

int GameWorld::addEntities(const std::vector<std::shared_ptr<Entity>> & entities) {
    int countAdded = 0;
    for(const auto & entity : entities) {
        entitiesToAdd.push_back(entity);
        ++countAdded;
    }
    return countAdded;
}

int GameWorld::removeEntity(const std::shared_ptr<Entity> & entity) {
    int countRemoved = 0;
    for(long i = entities.size() - 1; i >= 0; --i) {
        if(entity == entities[i]) {
            entities.erase(entities.begin() + i);
            ++countRemoved;
        }
    }
    for(long i = entitiesToAdd.size() - 1; i >= 0; --i) {
        if(entity == entitiesToAdd[i]) {
            entitiesToAdd.erase(entitiesToAdd.begin() + i);
            ++countRemoved;
        }
    }
    return countRemoved;
}

int GameWorld::removeEntities(const std::vector<std::shared_ptr<Entity>> & entities) {
    int countRemoved = 0;
    for(const auto & entity : entities) {
        countRemoved += removeEntity(entity);
    }
    return countRemoved;
}

void GameWorld::setupCamera() {
    Hack3dEngine & engine = Hack3dEngine::get();
    Graphics & graphics = engine.graphics();
    Vec2<int> windowSizeT = graphics.getWindowSize();
    Vec2<float> windowSize(windowSizeT.x, windowSizeT.y);

    double maxViewPortWorldUnits = Constants::MAX_VIEW_PORT_WORLD_UNITS_HEIGHT;
    Vec2<float> viewPort;

    /*if (windowSize.x > windowSize.y) {
        viewPort = Vec2<double>((windowSize.x / windowSize.y) * minViewPortWorldUnits, minViewPortWorldUnits);
    } else {
        viewPort = Vec2<double>(minViewPortWorldUnits, (windowSize.y / windowSize.x) * minViewPortWorldUnits);
    }*/
    if(windowSize.x > windowSize.y) {
        viewPort = Vec2<float>((windowSize.x / windowSize.y) * maxViewPortWorldUnits,
                               maxViewPortWorldUnits);
    } else {
        viewPort = Vec2<float>((windowSize.x / windowSize.y) * maxViewPortWorldUnits,
                               maxViewPortWorldUnits);
    }

    camera = Camera(CameraProjection::Orthogonal, viewPort);    // TODO create camera 2D class?
    camera.setPosition(glm::vec3(0.0f, 0.0f, Constants::Z_CAMERA_WORLD_2D));
    camera.setYaw(-90.0f);
    camera.setPitch(0.0f);
    camera.updateCameraVectors();
}

int GameWorld::addRemainingEntitiesToAdd() {
    int countAdded = 0;
    while(entitiesToAdd.size() > 0) {
        entities.push_back(entitiesToAdd[0]);
        entitiesToAdd[0]->create();
        entitiesToAdd[0]->resume();
        ++countAdded;
        entitiesToAdd.erase(entitiesToAdd.begin());
    }
    return countAdded;
}

void GameWorld::sortZOrder() {
    std::sort(entities.begin(), entities.end(),
              [](const std::shared_ptr<Entity> & a, const std::shared_ptr<Entity> & b) -> bool {
                  return a->zOrder < b->zOrder;
              });
}

void GameWorld::updateEntities(double deltaTime) {
    for(long i = 0; i < entities.size(); ++i) {
        if(!checkRemoveFlagAndRemove(entities[i])) {
            entities[i]->update(deltaTime);
            if(checkRemoveFlagAndRemove(entities[i])) {
                --i;
            }
        } else {
            --i;
        }
    }
}

bool GameWorld::checkRemoveFlagAndRemove(const std::shared_ptr<Entity> & entity) {
    return entity->removed && removeEntity(entity) > 0;
}

void GameWorld::updateCollisions(double deltaTime) {
    if(!bird->isAlive()) {
        return;
    }
    Rect<> rectBird(bird->pos.x - (bird->size.x * 0.5), bird->pos.y - (bird->size.y * 0.5),
                    bird->size.x, bird->size.y);
    Rect<> rectObs;
    for(long i = entities.size() - 1; i >= 0; --i) {
        if(auto * obs = dynamic_cast<Obstacle *>(entities[i].get())) {
            rectObs.set(obs->pos.x - (obs->size.x * 0.5), obs->pos.y - (obs->size.y * 0.5),
                        obs->size.x, obs->size.y);
            if(CollisionUtil<>::collision(rectBird, rectObs)) {
                if(auto * c = dynamic_cast<Consumable *>(obs)) {
                    bird->collision(c);
                    c->collision(bird.get());
                    break;
                } else {
                    birdCrash = true;
                    bird->collision(obs);
                    obs->collision(bird.get());
                    break;
                }
            }
        }
    }
}