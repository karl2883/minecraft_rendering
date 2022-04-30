#pragma once

#include "Camera.h"

enum PlayerMovement {
    FORWARDS,
    BACKWARDS,
    RIGHT,
    LEFT,
    DOWN,
    UP
};

class Player {
private:
    glm::vec3 pos;
    Camera camera;

    glm::vec3 frontVec;
    glm::vec3 rightVec;
    glm::vec3 upVec;
    glm::vec3 worldUpVec;
public:
    Player(glm::vec3 pos);

    void UpdateVectors();

    void Move(PlayerMovement movement, float amount);
    void Rotate(CameraRotation rotation, float degrees);
    void Tick();

    glm::vec3& GetPos() { return pos; }
    Camera& GetCamera() { return camera; }
};
