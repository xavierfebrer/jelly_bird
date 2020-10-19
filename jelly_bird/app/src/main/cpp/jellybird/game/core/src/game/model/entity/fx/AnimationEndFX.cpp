#include "../../../../../include/AnimationEndFX.h"

AnimationEndFX::AnimationEndFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                               const Rect<> & renderRect,
                               const std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> & animation) : FX(gameWorld,
                                                                                  zOrder),
                                                                               shader(shader),
                                                                               renderRect(
                                                                                       renderRect),
                                                                               animation(
                                                                                       animation) {
}

AnimationEndFX::~AnimationEndFX() {
}

void AnimationEndFX::update(double deltaTime) {
    if(animation) {
        animation->update(deltaTime);
        if(animation->hasEnded()) removed = true;
    } else {
        removed = true;
    }
}

void AnimationEndFX::render(double deltaTime) {
    if(!animation) return;
    auto qTRAnimationEnd = gameWorld.game.gameAssets->qTRAnimationEnd;
    qTRAnimationEnd->textureRegion2D = animation->getCurrentStep().getItem().get();
    qTRAnimationEnd->render(*shader,
            gameWorld.camera,
            renderRect.x - (renderRect.w * 0.5),
            renderRect.y - (renderRect.h * 0.5),
            -1,
            renderRect.w,
            renderRect.h,
            0,
            Vec2<>(1.0, 1.0),
            Vec2<>(0.5, 0.5),
                    Color(),
                    false,
                    false);
}

bool AnimationEndFX::hasEnded() {
    return animation && animation->hasEnded();
}
