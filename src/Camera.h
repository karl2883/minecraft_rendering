#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
    FORWARDS,
    BACKWARDS,
    RIGHT,
    LEFT,
    DOWN,
    UP
};

enum CameraRotation {
    YAW,
    PITCH
};

class Camera {
private:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    void UpdateVectors();
public:
    Camera() {}
    Camera(glm::vec3 pos, glm::vec3 worldUp, float yaw, float pitch);

    void Move(CameraMovement movement, float amount);
    void Rotate(CameraRotation rotation, float degrees);
    
    glm::vec3& GetPos() { return pos; }

    void SetPos(glm::vec3 newpos) { pos = newpos; }
    void SetRotation(float newyaw, float newpitch) { yaw = newyaw; pitch = newpitch; };
    
    glm::mat4 GetViewMatrix();
};
