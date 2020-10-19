#include "../../../../../include/ConsumablePickFX.h"
#include "../../../../../../../engine/core/include/ExpEase.h"

const Vec2<double> ConsumablePickFX::RENDERING_SIZE = Vec2<double>(
        16 * Constants::PIXEL_SIZE_W_UNIT, 16 * Constants::PIXEL_SIZE_W_UNIT);

ConsumablePickFX::ConsumablePickFX(GameWorld & gameWorld, double zOrder, Texture2DShader * shader,
                       const Rect<> & renderSize,
                       std::vector<std::shared_ptr<TextureRegion2D>> & tRsPick)
        : AnimationEndFX(gameWorld, zOrder, shader, renderSize,
                         std::make_shared<Animation<std::shared_ptr<TextureRegion2D>>>(
                                 AnimationStep<std::shared_ptr<TextureRegion2D>>::createList(
                                         tRsPick, 0.045), 1)), easeFade(std::make_unique<ExpEase>()) {

}

ConsumablePickFX::~ConsumablePickFX() {
}

void ConsumablePickFX::render(double deltaTime) {
    if(!animation) return;
    double timeLeft = animation->getTimeLeft();
    double duration = animation->getDuration();
    double fade = easeFade->update(duration, 0, 1.0 - (timeLeft / duration), EaseSlow::END) / duration;
    auto qTRAnimationEnd = gameWorld.game.gameAssets->qTRAnimationEnd;
    qTRAnimationEnd->textureRegion2D = animation->getCurrentStep().getItem().get();
    qTRAnimationEnd->render(*shader, gameWorld.camera, renderRect.x - (renderRect.w * 0.5),
                            renderRect.y - (renderRect.h * 0.5), -1, renderRect.w, renderRect.h, 0,
                            Vec2<>(1.0, 1.0), Vec2<>(0.5, 0.5), Color(fade), false, false);
}

