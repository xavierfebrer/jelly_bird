#include "../../../include/TextureRegion2D.h"

TextureRegion2D::TextureRegion2D(Texture2D * texture2D, int x, int y, int w, int h)
        : TextureRegion2D(texture2D, Rect<int>(x, y, w, h)) {
}

TextureRegion2D::TextureRegion2D(Texture2D * texture2D, const Rect<int> & region) : texture2D(
        texture2D), region(region) {
}

TextureRegion2D::~TextureRegion2D() {
}

void TextureRegion2D::activeBind() {
    texture2D->activeBind();
}

Texture2D * TextureRegion2D::getTexture2D() {
    return texture2D;
}

Rect<int> TextureRegion2D::getRegion() {
    return region;
}

