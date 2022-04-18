#include "Camera.h"

Camera::Camera(glm::vec3 cameraPos, glm::vec3 worldUp, float yaw, float pitch)
:pos{cameraPos}, worldUp{worldUp}, yaw{yaw}, pitch{pitch} {
    UpdateVectors();
}

void Camera::UpdateVectors() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::Move(CameraMovement movement, float amount) {
    if (movement == FORWARDS) {
        pos += front * amount;
    } else if (movement == BACKWARDS) {
        pos -= front * amount;
    } else if (movement == LEFT) {
        pos -= right * amount;
    } else if (movement == RIGHT) {
        pos += right * amount;
    } else if (movement == UP) {
        pos += worldUp * amount;
    } else if (movement == DOWN) {
        pos -= worldUp * amount;
    }
}

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
    UpdateVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(pos, pos + front, up);
}
