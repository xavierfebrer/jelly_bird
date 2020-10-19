#include "../../../../../include/Bird.h"
#include "../../../../../../../engine/core/include/Hack3dEngine.h"
#include "../../../../../include/GameAssets.h"
#include "../../../../../include/Obstacle.h"
#include "../../../../../include/Consumable.h"
#include "../../../../../include/Elixir.h"
#include "../../../../../include/Cherry.h"
#include "../../../../../include/CoinGold.h"
#include "../../../../../include/CoinSilver.h"
#include "../../../../../include/CoinBronze.h"
#include "../../../../../include/CoinDiamond.h"

const Vec2<double> Bird::DEFAULT_POS = Vec2<double>(0.0, 0.0);
const Vec2<double> Bird::DEFAULT_VEL = Vec2<double>(0.0, 0.0);
const Vec2<double> Bird::DEFAULT_ACC = Vec2<double>(0.0, 0.0);
const Vec2<double> Bird::RENDERING_SIZE = Vec2<double>(32 * Constants::PIXEL_SIZE_W_UNIT,
                                                       32 * Constants::PIXEL_SIZE_W_UNIT);
const Vec2<double> Bird::SIZE = Vec2<double>(14 * Constants::PIXEL_SIZE_W_UNIT,
                                             12 * Constants::PIXEL_SIZE_W_UNIT);
const Vec2<double> Bird::DEFAULT_GRAVITY_SCALE = Vec2<double>(6.0, 6.0);
const Vec2<double> Bird::DEFAULT_VEL_JUMP = Vec2<double>(6.5, 18);
const double Bird::DEFAULT_ROTATION = 0.0;
const double Bird::DEFAULT_ROTATION_SPEED = 0.0;
const Color Bird::DEFAULT_TINT = Color(1.0, 1.0, 1.0, 1.0);
const long Bird::DEFAULT_START_POINTS = 0;
const long Bird::DEFAULT_START_COINS = 0;
const double Bird::ANIMATION_FLY_SPEED_MAX = 4.5;
const double Bird::ANIMATION_FLY_SPEED_MIN = 0.5;
const double Bird::ANIMATION_FLY_ACC_IDLE = -5.5;
const int Bird::DEFAULT_LIFE = 1;
const double Bird::DEFAULT_MAX_ENERGY = 50;
const double Bird::DEFAULT_DRAIN_ENERGY_FLAP = 1;

Bird::Bird(GameWorld & gameWorld, double zOrder, double x, double y) : Entity(gameWorld, zOrder),
                                                                       posI(x, y),
                                                                       velI(Bird::DEFAULT_VEL),
                                                                       accI(gameWorld.gravity *
                                                                            Bird::DEFAULT_GRAVITY_SCALE),
                                                                       size(Bird::SIZE),
                                                                       points(Bird::DEFAULT_START_POINTS),
                                                                       coins(Bird::DEFAULT_START_COINS),
                                                                       rotation(DEFAULT_ROTATION),
                                                                       rotationSpeed(
                                                                               DEFAULT_ROTATION_SPEED),
                                                                       animationFlyExtraSpeed(1.0),
                                                                       stopped(true),
                                                                       life(DEFAULT_LIFE),
                                                                       energy(DEFAULT_MAX_ENERGY) {
}

Bird::~Bird() {
}

void Bird::create() {
    animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
            AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                    gameWorld.game.gameAssets->tRsBird, 0.05));
    shader = gameWorld.shader;
    qTRBird = gameWorld.game.gameAssets->qTRBird.get();
    sFlapWings = gameWorld.game.gameAssets->sFlapWings.get();
    sGoalReach = gameWorld.game.gameAssets->sGoalReach.get();
    sBirdHit = gameWorld.game.gameAssets->sBirdHit.get();
    sCoin = gameWorld.game.gameAssets->sCoin.get();
    sCoin2 = gameWorld.game.gameAssets->sCoin2.get();
    sCoin3 = gameWorld.game.gameAssets->sCoin3.get();
    sCoin4 = gameWorld.game.gameAssets->sCoin4.get();
    sEnergyGainElixir = gameWorld.game.gameAssets->sEnergyGainElixir.get();
    sEnergyGainCherry = gameWorld.game.gameAssets->sEnergyGainCherry.get();


    pos = posI;
    vel = velI;
    acc = accI;
    gravityScale = DEFAULT_GRAVITY_SCALE;
    tint = Bird::DEFAULT_TINT;
}

void Bird::resume() {
}

void Bird::pause() {
}

void Bird::update(double deltaTime) {
    if(isAlive()) {
        if(!stopped){
            accI = gameWorld.gravity * gravityScale;
            velI = vel;
            posI = pos;
            acc = accI;
            vel = Util::calcKinematicVel(velI, accI, deltaTime);
            pos = Util::calcKinematicPos(posI, velI, accI, deltaTime);
            if(wantsToJump(true) && canJump(true)) {
                performJump(true);
                animationFlyExtraSpeed = ANIMATION_FLY_SPEED_MAX;
            } else if(wantsToJump(false) && canJump(false)) {
                performJump(false);
                animationFlyExtraSpeed = ANIMATION_FLY_SPEED_MAX;
            } else {
                animationFlyExtraSpeed = Util::minMax(animationFlyExtraSpeed + deltaTime * ANIMATION_FLY_ACC_IDLE,
                                                   ANIMATION_FLY_SPEED_MIN, ANIMATION_FLY_SPEED_MAX);
            }
            updateAngle(deltaTime);
            animation->update(deltaTime, animationFlyExtraSpeed);
        } else {
            if(wantsToJump(true) && canJump(true)) {
                stopped = false;
                performJump(true);
                animationFlyExtraSpeed = ANIMATION_FLY_SPEED_MAX;
            } else if(wantsToJump(false) && canJump(false)) {
                stopped = false;
                performJump(false);
                animationFlyExtraSpeed = ANIMATION_FLY_SPEED_MAX;
            } else {
                animationFlyExtraSpeed = Util::minMax(animationFlyExtraSpeed + deltaTime * ANIMATION_FLY_ACC_IDLE,
                                                   ANIMATION_FLY_SPEED_MIN, ANIMATION_FLY_SPEED_MAX);
            }
            animation->update(deltaTime, animationFlyExtraSpeed);
        }
    } else {
        animation->update(deltaTime);
    }
}

void Bird::updateAngle(double deltaTime) {
    if(vel.y > 0) {
        if(rotation < 0) {
            rotationSpeed = 400 * Util::minMax(vel.y / (DEFAULT_VEL_JUMP.y * 0.5), 0.0, 1.0);
        } else if(rotation > 40) {
            rotationSpeed = 5 * Util::minMax(vel.y / (DEFAULT_VEL_JUMP.y * 0.5), 0.0, 1.0);
        } else if(rotation > 30) {
            rotationSpeed = 25 * Util::minMax(vel.y / (DEFAULT_VEL_JUMP.y * 0.5), 0.0, 1.0);
        } else if(rotation > 20) {
            rotationSpeed = 50 * Util::minMax(vel.y / (DEFAULT_VEL_JUMP.y * 0.5), 0.0, 1.0);
        } else {
            rotationSpeed = 200 * Util::minMax(vel.y / (DEFAULT_VEL_JUMP.y * 1), 0.0, 1.0);
        }
    } else {
        rotationSpeed = 400 * Util::minMax(vel.y / (DEFAULT_VEL_JUMP.y * 2.5), -1.0, 0.0);
    }
    rotation = Util::minMax(rotation + rotationSpeed * deltaTime, -90.0, 45.0);
}

bool Bird::wantsToJump(bool right) {
    for(int i = 0; i < 4; ++i) {
        if(Hack3dEngine::get().input().isPointerJustPressed(i)) {
            PointerInfo pointerInfo = Hack3dEngine::get().input().getPointerInfo(i);
            if(right){
                if(pointerInfo.x >= Hack3dEngine::get().graphics().getWindowSize().x * 0.5){
                    return true;
                }
            } else {
                if(pointerInfo.x < Hack3dEngine::get().graphics().getWindowSize().x * 0.5){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Bird::canJump(bool right) {
    return pos.y + (size.y * 0.5) < gameWorld.camera.getViewPort().y * 0.5 && energy >= DEFAULT_DRAIN_ENERGY_FLAP;
}

void Bird::performJump(bool right) {
    vel.set((right ? 1 : -1) * Bird::DEFAULT_VEL_JUMP.x, Bird::DEFAULT_VEL_JUMP.y);
    energy -= DEFAULT_DRAIN_ENERGY_FLAP;
    sFlapWings->play();
}

void Bird::render(double deltaTime) {
    bool flipX = vel.x < 0;
    qTRBird->textureRegion2D = animation->getCurrentStep().getItem().get();
    qTRBird->render(*shader, gameWorld.camera, pos.x - (Bird::RENDERING_SIZE.x * 0.5),
                    pos.y - (Bird::RENDERING_SIZE.y * 0.5), -1, Bird::RENDERING_SIZE.x,
                    Bird::RENDERING_SIZE.y, flipX ? -rotation : rotation, Vec2<>(1.0, 1.0),
                    Vec2<>(0.5, 0.5), Color(), flipX, false);
}

void Bird::collision(Entity * other) {
    if(isAlive()){
        if(auto * o = dynamic_cast<Obstacle *>(other)) {
            if(Elixir * wB = dynamic_cast<Elixir *>(other)) {
                addEnergy(*wB, true);
            } else if(Cherry * ch = dynamic_cast<Cherry *>(other)) {
                addEnergy(*ch, true);
            } else if(Consumable * c = dynamic_cast<Consumable *>(other)) {
                addCoins(*c, true);
            } else {
                --life;
                animation = std::make_unique<Animation<std::shared_ptr<TextureRegion2D>>>(
                        AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                                gameWorld.game.gameAssets->tRsBirdHit, 0.05));
                gameWorld.game.gameAssets->mGame->stop();
                sBirdHit->play();
            }
        }
    }
}

long Bird::getPoints() {
    return points;
}

void Bird::addPoints(long pts, bool notify) {
    this->points += pts;
    if(notify){
        sGoalReach->play();
    }
}

void Bird::addCoins(const Consumable & consumable, bool notify) {
    this->coins += consumable.value;
    addEnergy(consumable, false);
    if(notify){
        if(consumable.value >= CoinDiamond::VALUE) {
            sCoin4->play();
        } else if(consumable.value >= CoinGold::VALUE) {
            sCoin3->play();
        } else if(consumable.value >= CoinSilver::VALUE) {
            sCoin2->play();
        } else {
            sCoin->play();
        }
    }
}

void Bird::addEnergy(const Consumable & consumable, bool notify) {
    this->energy = Util::minMax(this->energy + energy, this->energy, DEFAULT_MAX_ENERGY);
    if(notify){
        if(consumable.energy >= Elixir::ENERGY) {
            sEnergyGainElixir->play();
        } else {
            sEnergyGainCherry->play();
        }
    }
}

bool Bird::isAlive() {
    return life > 0;
}
