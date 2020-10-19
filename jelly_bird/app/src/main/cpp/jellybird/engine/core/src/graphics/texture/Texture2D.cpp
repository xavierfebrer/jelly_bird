#include "../../../include/Texture2D.h"

Texture2D::Texture2D(const std::string & path) : Resource(), path(path) {
}

Texture2D::~Texture2D() {
}

std::string Texture2D::getPath() {
    return path;
}

Vec2<int> Texture2D::getSize() {
    return size;
}
