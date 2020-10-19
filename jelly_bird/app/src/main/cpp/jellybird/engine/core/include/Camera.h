#ifndef CAMERA_H
#define CAMERA_H

#include "BaseInclude.h"
#include "Vec2.h"

enum class CameraProjection {
    Perspective, Orthogonal
};

class Camera {
public:
    static const float DEFAULT_YAW;
    static const float DEFAULT__PITCH;
    static const float DEFAULT_FOVY;

    CameraProjection projection;

    Camera(CameraProjection projection, const Vec2<float> & viewPort,
           glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = DEFAULT_YAW,
           float pitch = DEFAULT__PITCH);
    Camera(CameraProjection projection, const Vec2<float> & viewPort, float posX, float posY,
           float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    virtual ~Camera();

    virtual void updateCameraVectors();

    virtual glm::mat4 getModelMatrix();
    virtual glm::mat4 getViewMatrix();
    virtual glm::mat4 getProjectionMatrix();
    virtual glm::mat4 getViewProjectionMatrix();
    virtual void setPosition(glm::vec3 position);
    virtual void setPosition(float x, float y, float z);
    virtual glm::vec3 getPosition();
    virtual glm::vec3 getFront();
    virtual void setYaw(float yaw);
    virtual float getYaw();
    virtual void setPitch(float pitch);
    virtual float getPitch();
    virtual void setFOVY(float fOVY);
    virtual float getFOVY();
    virtual Vec2<float> getViewPort();
    virtual void setViewPort(const Vec2<float> & viewPort);
    virtual Vec2<> screenToWorldSpaceCoords(const Vec2<> & screenCoords, const Vec2<int> & screenSize);
protected:
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 viewProjectionMatrix; // viewProjectionMatrix == projectionMatrix * viewMatrix, saves multiplications
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float fOVY;
    Vec2<float> viewPort;
};

#endif