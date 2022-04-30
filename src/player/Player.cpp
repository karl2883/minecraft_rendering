#include "Player.h"
#include <iostream>
#include <glm/gtx/io.hpp>

Player::Player(glm::vec3 pos) 
:camera(pos, -90.0f, 0.0f)
{
    worldUpVec = glm::vec3(0.0f, 1.0f, 0.0f);
    UpdateVectors();
}

void Player::UpdateVectors() {
    float yaw = camera.GetYaw();
    float pitch = camera.GetPitch();

    frontVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontVec.y = sin(glm::radians(pitch));
    frontVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontVec = glm::normalize(frontVec);

    rightVec = glm::normalize(glm::cross(frontVec, worldUpVec));
    upVec = glm::normalize(glm::cross(rightVec, frontVec));
}

void Player::Move(PlayerMovement movement, float amount) {
    if (movement == FORWARDS) {
        pos += frontVec * amount;
    } else if (movement == BACKWARDS) {
        pos -= frontVec * amount;
    } else if (movement == LEFT) {
        pos -= rightVec * amount;
    } else if (movement == RIGHT) {
        pos += rightVec * amount;
    } else if (movement == UP) {
        pos += worldUpVec * amount;
    } else if (movement == DOWN) {
        pos -= worldUpVec * amount;
    }
}

void Player::Rotate(CameraRotation rotation, float degrees) {
    camera.Rotate(rotation, degrees);
}

void Player::Tick() {
    UpdateVectors();
    camera.SetFrontVec(frontVec);
    camera.SetUpVec(upVec);
    camera.SetPos(pos);
}
