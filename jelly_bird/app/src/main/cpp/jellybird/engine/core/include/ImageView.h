#ifndef IMAGE_VIEW_H
#define IMAGE_VIEW_H

#include "View.h"
#include "Padding.h"
#include "QuadTextureRegion2D.h"
#include "Animation.h"

template<typename G>
class ImageView : public View<G> {
public:
    ImageView(G & game, const Rect<> & bounds, const Padding & padding,
              QuadTextureRegion2D & qTRImageView,
              std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationIdle,
              std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationDisabled,
              std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGIdle,
              std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGDisabled);
    virtual ~ImageView() override;

    virtual void resume() override;
    virtual bool
    input(double deltaTime, const PointerEventInfo & pointerEventInfo, bool consumed) override;
    virtual void update(double deltaTime) override;
    virtual void render(double deltaTime, Camera & camera, Texture2DShader & shader) override;
    virtual void resize(double width, double height) override;
    virtual void pause() override;
    virtual void setEnabled(bool enabled) override;
    virtual void setPadding(const Padding & padding);
    virtual const Padding & getPadding();
    virtual double getPaddingWidth();
    virtual double getPaddingHeight();
protected:
    Padding padding;
    QuadTextureRegion2D & qTRImageView;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> currentContentAnimation;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> currentBGAnimation;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationIdle;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationDisabled;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGIdle;
    std::shared_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGDisabled;
};

template<typename G>
ImageView<G>::ImageView(G & game, const Rect<> & bounds, const Padding & padding,
                        QuadTextureRegion2D & qTRImageView,
                        std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationIdle,
                        std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationDisabled,
                        std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGIdle,
                        std::unique_ptr<Animation<std::shared_ptr<TextureRegion2D>>> animationBGDisabled)
        : View<G>(game, bounds), padding(padding), qTRImageView(qTRImageView),
          animationIdle(std::move(animationIdle)), animationDisabled(std::move(animationDisabled)) {
    setEnabled(true);
    currentContentAnimation = this->animationIdle;
    currentBGAnimation = this->animationBGIdle;
}

template<typename G>
ImageView<G>::~ImageView() {
}

template<typename G>
void ImageView<G>::resume() {
}

template<typename G>
bool
ImageView<G>::input(double deltaTime, const PointerEventInfo & pointerEventInfo, bool consumed) {
    return false;
}

template<typename G>
void ImageView<G>::update(double deltaTime) {
    View<G>::update(deltaTime);
    if(currentContentAnimation) {
        currentContentAnimation->update(deltaTime);
    }
    if(currentBGAnimation) {
        currentBGAnimation->update(deltaTime);
    }
}

template<typename G>
void ImageView<G>::render(double deltaTime, Camera & camera, Texture2DShader & shader) {
    if(currentBGAnimation) {
        qTRImageView.textureRegion2D = currentBGAnimation->getCurrentStep().getItem().get();
        qTRImageView.render(shader, camera, this->bounds.x, this->bounds.y, -1, this->bounds.w,
                            this->bounds.h);
    }
    if(currentContentAnimation) {
        qTRImageView.textureRegion2D = currentContentAnimation->getCurrentStep().getItem().get();
        qTRImageView.render(shader, camera, this->bounds.x, this->bounds.y, -1, this->bounds.w,
                            this->bounds.h);
    }
}

template<typename G>
void ImageView<G>::resize(double width, double height) {
}

template<typename G>
void ImageView<G>::pause() {
}

template<typename G>
void ImageView<G>::setEnabled(bool enabled) {
    if(View<G>::isEnabled() != enabled) {
        currentContentAnimation = enabled ? animationIdle : animationDisabled;
        currentBGAnimation = enabled ? animationBGIdle : animationBGDisabled;
        if(currentContentAnimation) {
            currentContentAnimation->restart();
        }
        if(currentBGAnimation) {
            currentBGAnimation->restart();
        }
    }
    View<G>::setEnabled(enabled);
}

template<typename G>
void ImageView<G>::setPadding(const Padding & padding) {
    this->padding = padding;
}

template<typename G>
const Padding & ImageView<G>::getPadding() {
    return padding;
}

template<typename G>
double ImageView<G>::getPaddingWidth() {
    return this->bounds.w * padding.getH();
}

template<typename G>
double ImageView<G>::getPaddingHeight() {
    return this->bounds.h * padding.getV();
}

#endif