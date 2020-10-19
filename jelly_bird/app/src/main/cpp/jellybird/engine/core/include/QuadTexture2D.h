#ifndef QUADTEXTURE2D_H
#define QUADTEXTURE2D_H

#include "Resource.h"
#include "Texture2D.h"
#include "Texture2DShader.h"
#include "Color.h"
#include "Camera.h"

class QuadTexture2D : public Resource {
public:
    Texture2D* texture2D;

    QuadTexture2D(Texture2D* texture2D = nullptr);
    virtual ~QuadTexture2D();

    Texture2D* getTexture2D();
    void setTexture2D(Texture2D* texture2D);
    virtual void
    render(Texture2DShader & shader, Camera & camera, double leftX, double bottomY, double depth, double width, double height, double rotationDeg = 0.0, const Vec2<double> & scale = Vec2<>(
            1.0, 1.0), const Vec2<double> & origin = Vec2<>(0.0, 0.0), const Color & tint = Color(
            1.0, 1.0, 1.0, 1.0), bool flipX = false, bool flipY = false, const glm::vec2 & offset = glm::vec2(0, 0)) = 0;
};

#endif