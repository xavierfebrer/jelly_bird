#ifndef ANDROID_OPEN_GL_QUAD_TEXTURE_REGION_2D_H
#define ANDROID_OPEN_GL_QUAD_TEXTURE_REGION_2D_H

#include "../../core/include/QuadTextureRegion2D.h"
#include "AndroidOpenGLTextureRegion2D.h"

class AndroidOpenGLQuadTextureRegion2D : public QuadTextureRegion2D {
public:
    unsigned int quadVBO;
    unsigned int quadVAO;

    AndroidOpenGLQuadTextureRegion2D(AndroidOpenGLTextureRegion2D * textureRegion2D = nullptr);
    virtual ~AndroidOpenGLQuadTextureRegion2D() override;

    virtual bool load() override;
    virtual bool unLoad() override;
    virtual void
    render(Texture2DShader & shader, Camera & camera, double leftX, double bottomY, double depth, double width, double height, double rotationDeg = 0.0, const Vec2<double> & scale = Vec2<>(
            1.0, 1.0), const Vec2<double> & origin = Vec2<>(0.0, 0.0), const Color & tint = Color(
            1.0, 1.0, 1.0, 1.0), bool flipX = false, bool flipY = false) override;
};

#endif