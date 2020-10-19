#include "../../../include/AndroidOpenGLQuadTexture2D.h"

AndroidOpenGLQuadTexture2D::AndroidOpenGLQuadTexture2D(AndroidOpenGLTexture2D * texture2D)
        : QuadTexture2D(texture2D) {
}

AndroidOpenGLQuadTexture2D::~AndroidOpenGLQuadTexture2D() {
    unLoad();
}

bool AndroidOpenGLQuadTexture2D::load() {
    if(!loaded) {
        quadVAO = 0;       // Quad VAO id
        quadVBO = 0;       // Quad VBO id for individual buffer

        float vertices[] = {
                // vertices       Texture Coords
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,};

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

bool AndroidOpenGLQuadTexture2D::unLoad() {
    if(loaded) {
        glBindVertexArray(0);
        glDeleteBuffers(1, &quadVBO);
        glDeleteVertexArrays(1, &quadVAO);
        loaded = false;
    }
    return !loaded;
}

void AndroidOpenGLQuadTexture2D::render(Texture2DShader & shader, Camera & camera, double leftX,
                                        double bottomY, double depth, double width, double height,
                                        double rotationDeg, const Vec2<double> & scale,
                                        const Vec2<double> & origin, const Color & tint, bool flipX, bool flipY,
                                        const glm::vec2 & offset) {
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
    shader.setOffset(offset);
    shader.setScale(glm::vec3(1.0f, 1.0f, 0.0f));
    shader.setTint(tint);
    shader.setFlip(flipX, flipY);

    // active texture
    if(texture2D) {
        texture2D->activeBind();
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