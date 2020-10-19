#ifndef QUAD_TEXTURE_REGION_2D_H
#define QUAD_TEXTURE_REGION_2D_H

#include "Resource.h"
#include "TextureRegion2D.h"
#include "Texture2DShader.h"
#include "Color.h"
#include "Camera.h"

class QuadTextureRegion2D : public Resource {
public:
    TextureRegion2D* textureRegion2D;

    QuadTextureRegion2D(TextureRegion2D* textureRegion2D = nullptr);
    virtual ~QuadTextureRegion2D();

    TextureRegion2D* getTextureRegion2D();
    void setTextureRegion2D(TextureRegion2D* textureRegion2D);
    virtual void
    render(Texture2DShader & shader, Camera & camera, double leftX, double bottomY, double depth, double width, double height, double rotationDeg = 0.0, const Vec2<double> & scale = Vec2<>(
            1.0, 1.0), const Vec2<double> & origin = Vec2<>(0.0, 0.0), const Color & tint = Color(
            1.0, 1.0, 1.0, 1.0), bool flipX = false, bool flipY = false) = 0;
};

#endif