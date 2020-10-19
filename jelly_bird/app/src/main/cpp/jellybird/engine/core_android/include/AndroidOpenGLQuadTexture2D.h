#ifndef ANDROID_OPEN_GL_QUAD_TEXTURE_2D_H
#define ANDROID_OPEN_GL_QUAD_TEXTURE_2D_H

#include "../../core/include/QuadTexture2D.h"
#include "AndroidOpenGLTexture2D.h"

class AndroidOpenGLQuadTexture2D : public QuadTexture2D {
public:
    unsigned int quadVBO;
    unsigned int quadVAO;

    AndroidOpenGLQuadTexture2D(AndroidOpenGLTexture2D * texture2D = nullptr);
    virtual ~AndroidOpenGLQuadTexture2D() override;

    virtual bool load() override;
    virtual bool unLoad() override;
    virtual void
    render(Texture2DShader & shader, Camera & camera, double leftX, double bottomY, double depth, double width, double height, double rotationDeg = 0.0, const Vec2<double> & scale = Vec2<>(
            1.0, 1.0), const Vec2<double> & origin = Vec2<>(0.0, 0.0), const Color & tint = Color(
            1.0, 1.0, 1.0, 1.0), bool flipX = false, bool flipY = false, const glm::vec2 & offset = glm::vec2(0, 0)) override;
};

#endif