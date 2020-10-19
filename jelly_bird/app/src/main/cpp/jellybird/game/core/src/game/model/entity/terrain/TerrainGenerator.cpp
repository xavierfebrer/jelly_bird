#include "../../../../../include/TerrainGenerator.h"
#include "../../../../../include/Bird.h"
#include "../../../../../include/Obstacle.h"
#include "../../../../../include/PointGoal.h"
#include "../../../../../include/Dirt1x1.h"
#include "../../../../../include/GrassDirt1x1.h"
#include "../../../../../include/Wall.h"
#include "../../../../../include/CoinGold.h"
#include "../../../../../include/CoinSilver.h"
#include "../../../../../include/CoinBronze.h"
#include "../../../../../include/CoinDiamond.h"
#include "../../../../../include/Elixir.h"
#include "../../../../../include/Cherry.h"

const double TerrainGenerator::MAX_DISTANCE_BETWEEN_ELIXIR = 100;
const double TerrainGenerator::MAX_DISTANCE_BETWEEN_CHERRY = 50;

TerrainGenerator::TerrainGenerator(GameWorld & gameWorld, double zOrder, double zOrderWall,
                                   double bottomY, double topY, double horizontalReach,
                                   double startX) : Entity(gameWorld, zOrder),
                                                    zOrderWall(zOrderWall), bottomY(bottomY),
                                                    topY(topY), horizontalReach(horizontalReach),
                                                    startX(startX) {
}

TerrainGenerator::~TerrainGenerator() {
}

void TerrainGenerator::create() {
    clear();
    addWall(parsedX, bottomY + (Wall::SIZE.y * 0.5) - 3.5);
}

void TerrainGenerator::resume() {
}

void TerrainGenerator::pause() {
}

void TerrainGenerator::update(double deltaTime) {
    parseRemaining();
}

void TerrainGenerator::render(double deltaTime) {
}

void TerrainGenerator::collision(Entity * other) {
}

void TerrainGenerator::clear() {
    resetValues();
}

void TerrainGenerator::resetValues() {
    setDistancePercent(1.0f);
    setHolePercent(1.0f);
    setCoinPercent(0.025f);
    parsedX = startX;
    lastWallX = parsedX - (getDistanceBetweenWalls());
    lastElixirX = startX;
    lastCherryX = startX;
    minDistanceBetweenWalls = 5.55;
    offsetBetweenWalls = 3.00;
    minHoleSize = 5.150;
    offsetHoleSize = 3.00;
    topBottomPadding = 2.5;
    imparFloor = true;
}

void TerrainGenerator::parseRemaining() {
    while(parsedX < gameWorld.bird->pos.x + horizontalReach) {
        imparFloor = true;
        for(int i = 0; i < 3; ++i) {
            if(i == 0) {
                gameWorld.addEntity(std::make_shared<GrassDirt1x1>(gameWorld, zOrder, parsedX +
                                                                                      (imparFloor ?
                                                                                       GrassDirt1x1::SIZE
                                                                                               .x *
                                                                                       0.5 : 0),
                                                                   bottomY - (GrassDirt1x1::SIZE.y *
                                                                              (i + 4))));
            } else {
                gameWorld.addEntity(std::make_shared<Dirt1x1>(gameWorld, zOrder, parsedX +
                                                                                 (imparFloor ?
                                                                                  Dirt1x1::SIZE.x *
                                                                                  0.5 : 0),
                                                              bottomY -
                                                              (Dirt1x1::SIZE.y * (i + 4))));
            }
            imparFloor = !imparFloor;
        }
        double distanceBetweenWalls = getDistanceBetweenWalls();
        if(parsedX > gameWorld.bird->pos.x + (horizontalReach * 0.5) &&
           parsedX > lastWallX + distanceBetweenWalls) {
            double holeSize = getHoleSize();
            lastWallX = parsedX + Wall::SIZE.x;
            double maxHoleY = topY - holeSize * 0.5 - topBottomPadding;
            double minHoleY = bottomY + holeSize * 0.5 + topBottomPadding;
            double holeY = minHoleY + (maxHoleY - minHoleY) * Util::random(0.0, 1.0);

            Vec2<> wallTopPos = Vec2<>(parsedX + (Wall::SIZE.x * 0.5),
                                       holeY + (holeSize * 0.5) + (Wall::SIZE.y * 0.5));
            Vec2<> wallBottomPos = Vec2<>(parsedX + (Wall::SIZE.x * 0.5),
                                          holeY - (holeSize * 0.5) - (Wall::SIZE.y * 0.5));
            std::shared_ptr<Wall> topWall = addWall(wallTopPos.x, wallTopPos.y);
            addWall(wallBottomPos.x, wallBottomPos.y);

            gameWorld.addEntity(std::make_shared<PointGoal>(gameWorld, zOrderWall,
                                                            parsedX + (Wall::SIZE.x * 0.5),
                                                            PointGoal::DEFAULT_POINTS));
        } else if(parsedX > lastWallX + Wall::SIZE.x) {
            maybeAddCoin();
            maybeAddEnergy();
        }
        parsedX += GrassDirt1x1::SIZE.x;
    }
}

void TerrainGenerator::maybeAddCoin() {
    double addCoin = Util::random();
    double coinPercent = getCoinPercent();
    double minProb = 0.20 * coinPercent;
    if(addCoin < minProb) {
        gameWorld.addEntity(std::make_shared<CoinDiamond>(gameWorld, zOrderWall, parsedX, bottomY + Util::random(0.0, (topY - bottomY))));
    } else if(addCoin < 3 * minProb + minProb) {
        gameWorld.addEntity(std::make_shared<CoinGold>(gameWorld, zOrderWall, parsedX, bottomY + Util::random(0.0, (topY - bottomY))));
    } else if(addCoin < 3 * (3 * minProb + minProb) + (3 * minProb + minProb)) {
        gameWorld.addEntity(std::make_shared<CoinSilver>(gameWorld, zOrderWall, parsedX, bottomY + Util::random(0.0, (topY - bottomY))));
    } else if(addCoin < 3 * (3 * (3 * minProb + minProb) + (3 * minProb + minProb)) + (3 * (3 * minProb + minProb) + (3 * minProb + minProb))) {
        gameWorld.addEntity(std::make_shared<CoinBronze>(gameWorld, zOrderWall, parsedX, bottomY + Util::random(0.0, (topY - bottomY))));
    }
}

void TerrainGenerator::maybeAddEnergy() {
    double random = Util::random();
    if(gameWorld.bird->pos.x - lastElixirX > MAX_DISTANCE_BETWEEN_ELIXIR || random < 0.01){
        gameWorld.addEntity(std::make_shared<Elixir>(gameWorld, zOrderWall, parsedX, bottomY + Util::random(0.0, (topY - bottomY))));
        lastElixirX = gameWorld.bird->pos.x;
    } else if(gameWorld.bird->pos.x - lastCherryX > MAX_DISTANCE_BETWEEN_CHERRY || random < 0.02){
        gameWorld.addEntity(std::make_shared<Cherry>(gameWorld, zOrderWall, parsedX, bottomY + Util::random(0.0, (topY - bottomY))));
        lastCherryX = gameWorld.bird->pos.x;
    }
}

std::shared_ptr<Wall> TerrainGenerator::addWall(double x, double y) {
    std::shared_ptr<Wall> wall = std::make_shared<Wall>(gameWorld, zOrderWall, x, y);
    gameWorld.addEntity(wall);
    return wall;
}

void TerrainGenerator::setDistancePercent(float percent) {
    this->distancePercent = Util::minMax(percent, 0.0f, 1.0f);
}

void TerrainGenerator::setHolePercent(float percent) {
    this->holePercent = Util::minMax(percent, 0.0f, 1.0f);
}

void TerrainGenerator::setCoinPercent(float percent) {
    this->coinPercent = Util::minMax(percent, 0.0f, 1.0f);
}

double TerrainGenerator::getDistanceBetweenWalls() {
    return minDistanceBetweenWalls + Util::random(0.0, offsetBetweenWalls * distancePercent);
}

double TerrainGenerator::getHoleSize() {
    return minHoleSize + Util::random(0.0, offsetHoleSize * holePercent);
}

double TerrainGenerator::getCoinPercent() {
    return coinPercent;
}
