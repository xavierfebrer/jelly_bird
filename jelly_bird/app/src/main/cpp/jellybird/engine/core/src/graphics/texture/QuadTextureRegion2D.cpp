#include "../../../include/QuadTextureRegion2D.h"

QuadTextureRegion2D::QuadTextureRegion2D(TextureRegion2D* textureRegion2D) : Resource(), textureRegion2D(textureRegion2D) {

}

QuadTextureRegion2D::~QuadTextureRegion2D() {

}

TextureRegion2D * QuadTextureRegion2D::getTextureRegion2D() {
    return textureRegion2D;
}

void QuadTextureRegion2D::setTextureRegion2D(TextureRegion2D * textureRegion2D) {
    this->textureRegion2D = textureRegion2D;
}

