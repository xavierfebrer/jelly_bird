#include "../../../include/AndroidOpenGLQuadTextureRegion2D.h"

AndroidOpenGLQuadTextureRegion2D::AndroidOpenGLQuadTextureRegion2D(
        AndroidOpenGLTextureRegion2D * textureRegion2D) : QuadTextureRegion2D(textureRegion2D) {
}

AndroidOpenGLQuadTextureRegion2D::~AndroidOpenGLQuadTextureRegion2D() {
    unLoad();
}

bool AndroidOpenGLQuadTextureRegion2D::load() {
    if(!loaded) {
        quadVAO = 0;       // Quad VAO id
        quadVBO = 0;       // Quad VBO id for individual buffer

        float vertices[] = {
                // vertices       Texture Coords
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,};

        // Generate quad VAO/VBO ids
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);

        // Fill VBO buffer
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        // Link vertex attributes
        glEnableVertexAttribArray(0);    // scene.vs in vec3 aPos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(1);    // scene.vs in vec2 aTexCoords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                              (void *) (3 * sizeof(float)));
        loaded = true;
    }
    return loaded;
}

bool AndroidOpenGLQuadTextureRegion2D::unLoad() {
    if(loaded) {
        glBindVertexArray(0);
        glDeleteBuffers(1, &quadVBO);
        glDeleteVertexArrays(1, &quadVAO);
        loaded = false;
    }
    return !loaded;
}

void
AndroidOpenGLQuadTextureRegion2D::render(Texture2DShader & shader, Camera & camera, double leftX,
                                         double bottomY, double depth, double width, double height,
                                         double rotationDeg, const Vec2<double> & scale,
                                         const Vec2<double> & origin, const Color & tint, bool flipX, bool flipY) {
    // use shader
    shader.use();

    // set mvp matrix: in order apply operations: 1. scale, 2. rotate, 3. translate
    glm::mat4 model = glm::mat4(1.0f);

    // third translate
    model = glm::translate(model, glm::vec3(leftX, bottomY, depth));

    // second rotate
    model = glm::translate(model, glm::vec3(origin.x * width * scale.x, origin.y * height * scale.y,
                                            depth));
    model = glm::rotate(model, (float) glm::radians(rotationDeg), glm::vec3(0.0, 0.0, 1.0));
    model = glm::translate(model,
                           glm::vec3(-origin.x * width * scale.x, -origin.y * height * scale.y,
                                     depth));

    // first scale
    model = glm::scale(model, glm::vec3(width * scale.x, height * scale.y, 1.0));

    shader.setMVP(camera.getViewProjectionMatrix() * model);
    Rect<int> region = textureRegion2D->getRegion();
    Vec2<int> tSize = textureRegion2D->getTexture2D()->getSize();
    glm::vec2 sc = glm::vec2(((float) region.w) / ((float) tSize.x),
              ((float) region.h) / ((float) tSize.y));
    glm::vec2 oS = glm::vec2(((float) region.x) / ((float) tSize.x),
              (1.0f - (((float) region.y) / ((float) tSize.y))) - sc.y );  // preferred to map from top left
    shader.setOffset(oS);
    shader.setScale(sc);
    shader.setTint(tint);
    shader.setFlip(flipX, flipY);

    // active texture
    Texture2D * text2D = textureRegion2D->getTexture2D();
    if(text2D) {
        text2D->activeBind();
    }

    // bind quad
    glBindVertexArray(quadVAO);

    // draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // unbind (optional?)
    glBindTexture(GL_TEXTURE_2D, 0);    // Unbind textures
    glBindVertexArray(0);               // Unbind VAO
    shader.stopUsing();
}
