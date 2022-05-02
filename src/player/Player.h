#pragma once

#include "Camera.h"
#include "../world/World.h"
#include "Ray.h"

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

    World& world;

    constexpr static const float RAY_STEP_DIST = 0.05f;
    constexpr static const float RAY_DISTANCE = 8.0f;
public:
    Player(glm::vec3 pos, World& world);

    void UpdateVectors();

    void Move(PlayerMovement movement, float amount);
    void DestroyBlock();
    void SetBlock();
    void Rotate(CameraRotation rotation, float degrees);
    void Tick();

    glm::vec3& GetPos() { return pos; }
    Camera& GetCamera() { return camera; }
};
