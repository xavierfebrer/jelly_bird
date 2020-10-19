#ifndef BIRD_H
#define BIRD_H

#include "Entity.h"
#include "../../../engine/core/include/QuadTexture2D.h"
#include "../../../engine/core/include/Color.h"
#include "../../../engine/core/include/Animation.h"
#include "../../../engine/core/include/AnimationStep.h"
#include "../../../engine/core/include/Hack3dEngine.h"

class Consumable;

class Bird : public Entity {
public:
    static const Vec2<double> DEFAULT_POS;
    static const Vec2<double> DEFAULT_VEL;
    static const Vec2<double> DEFAULT_ACC;
    static const Vec2<double> RENDERING_SIZE;
    static const Vec2<double> SIZE;
    static const Vec2<double> DEFAULT_GRAVITY_SCALE;
    static const Vec2<double> DEFAULT_VEL_JUMP;
    static const double DEFAULT_ROTATION;
    static const double DEFAULT_ROTATION_SPEED;
    static const Color DEFAULT_TINT;
    static const long DEFAULT_START_POINTS;
    static const long DEFAULT_START_COINS;
    static const double ANIMATION_FLY_SPEED_MAX;
    static const double ANIMATION_FLY_SPEED_MIN;
    static const double ANIMATION_FLY_ACC_IDLE;
    static const int DEFAULT_LIFE;
    static const double DEFAULT_MAX_ENERGY;
    static const double DEFAULT_DRAIN_ENERGY_FLAP;

    Texture2DShader * shader;
    QuadTextureRegion2D * qTRBird;
    Sound * sFlapWings;
    Sound * sGoalReach;
    Sound * sBirdHit;
    Sound * sCoin;
    Sound * sCoin2;
    Sound * sCoin3;
    Sound * sCoin4;
    Sound * sEnergyGainElixir;
    Sound * sEnergyGainCherry;
    Vec2<double> posI;
    Vec2<double> velI;
    Vec2<double> accI;
    Vec2<double> pos;
    Vec2<double> vel;
    Vec2<double> acc;
    Vec2<double> size;
    Vec2<double> gravityScale;
    Color tint;
    long points;
    long coins;
    double rotation;
    double rotationSpeed;
    std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animation;
    double animationFlyExtraSpeed;
    bool stopped;

    Bird(GameWorld & gameWorld, double zOrder, double x = DEFAULT_POS.x, double y = DEFAULT_POS.y);
    virtual ~Bird() override;

    virtual void create() override;
    virtual void resume() override;
    virtual void pause() override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime) override;
    virtual void collision(Entity * other) override;

    virtual long getPoints();
    virtual void addPoints(long pts, bool notify);
    virtual void addCoins(const Consumable & consumable, bool notify);
    virtual void addEnergy(const Consumable & consumable, bool notify);
    virtual bool isAlive();
protected:
    int life;
    double energy;

    bool wantsToJump(bool right);
    bool canJump(bool right);
    void performJump(bool right);
    void updateAngle(double deltaTime);
};

#endif