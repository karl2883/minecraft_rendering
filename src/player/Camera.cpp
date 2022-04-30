#include "Camera.h"

Camera::Camera(glm::vec3 cameraPos, float yaw, float pitch)
:pos{cameraPos}, yaw{yaw}, pitch{pitch} {}


void Camera::Rotate(CameraRotation rotation, float degrees) {
    if (rotation == YAW) {
        yaw += degrees;
    } else if (rotation == PITCH) {
        pitch += degrees;
        if(pitch > 89.0f)
            pitch =  89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;
    }
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(pos, pos + frontVec, upVec);
}
