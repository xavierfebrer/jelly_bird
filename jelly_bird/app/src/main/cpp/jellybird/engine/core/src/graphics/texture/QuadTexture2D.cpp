#include "../../../include/QuadTexture2D.h"

QuadTexture2D::QuadTexture2D(Texture2D* texture2D) : Resource(), texture2D(texture2D) {

}

QuadTexture2D::~QuadTexture2D() {

}

Texture2D * QuadTexture2D::getTexture2D() {
    return texture2D;
}

void QuadTexture2D::setTexture2D(Texture2D * texture2D) {
    this->texture2D = texture2D;
}

