#include "../../../../core/include/Camera.h"
#include "../../../../core/include/Hack3dEngine.h"

const float Camera::DEFAULT_YAW = -90.0f;
const float Camera::DEFAULT__PITCH = 0.0f;
const float Camera::DEFAULT_FOVY = 60.0f;

Camera::Camera(CameraProjection projection, const Vec2<float> & viewPort, glm::vec3 position,
               glm::vec3 up, float yaw, float pitch) : projection(projection),
                                                       front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                                       fOVY(Camera::DEFAULT_FOVY),
                                                       viewPort(viewPort) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(CameraProjection projection, const Vec2<float> & viewPort, float posX, float posY,
               float posZ, float upX, float upY, float upZ, float yaw, float pitch) : projection(
        projection), front(glm::vec3(0.0f, 0.0f, -1.0f)), fOVY(Camera::DEFAULT_FOVY), viewPort(
        viewPort) {
    this->position = glm::vec3(posX, posY, posZ);
    this->worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Camera::~Camera() {
}

void Camera::updateCameraVectors() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));

    modelMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(position, position + front, up);
    if(projection == CameraProjection::Perspective) {
        projectionMatrix = glm::perspective(glm::radians(fOVY), viewPort.x / viewPort.y, 0.01f,
                                            1000.0f);
    } else {
        projectionMatrix = glm::ortho(-viewPort.x * 0.5f, viewPort.x * 0.5f, -viewPort.y * 0.5f,
                                      viewPort.y * 0.5f, 0.01f, 1000.0f);
    }
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}

glm::mat4 Camera::getModelMatrix() {
    return modelMatrix;
}

glm::mat4 Camera::getViewMatrix() {
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
    return projectionMatrix;
}

glm::mat4 Camera::getViewProjectionMatrix() {
    return viewProjectionMatrix;
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
}

void Camera::setPosition(float x, float y, float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

glm::vec3 Camera::getFront() {
    return this->front;
}

float Camera::getYaw() {
    return yaw;
}

void Camera::setYaw(float yaw) {
    this->yaw = yaw;
}

float Camera::getPitch() {
    return pitch;
}

void Camera::setPitch(float pitch) {
    this->pitch = pitch;
}

float Camera::getFOVY() {
    return fOVY;
}

void Camera::setFOVY(float fOVY) {
    this->fOVY = fOVY;
}

Vec2<float> Camera::getViewPort() {
    return viewPort;
}

void Camera::setViewPort(const Vec2<float> & viewPort) {
    this->viewPort = viewPort;
}

Vec2<> Camera::screenToWorldSpaceCoords(const Vec2<> & screenCoords, const Vec2<int> & screenSize) {
    // screen coords top left = 0, 0
    // camera coords center = 0, 0
    Vec2<> pixelsPerWorldUnit(screenSize.x / viewPort.x, screenSize.y / viewPort.y);
    Vec2<> toOrigin(screenCoords.x - (screenSize.x * 0.5),
                    (screenSize.y - screenCoords.y) - (screenSize.y * 0.5));
    Vec2<> toWorldScale((toOrigin / pixelsPerWorldUnit) - Vec2<>(position.x, position.y));
    return toWorldScale;
}
