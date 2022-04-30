#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraRotation {
    YAW,
    PITCH
};


class Camera {
private:
    glm::vec3 pos;
    glm::vec3 frontVec;
    glm::vec3 upVec;

    float yaw;
    float pitch;
public:
    Camera() {}
    Camera(glm::vec3 pos, float yaw, float pitch);

    void Rotate(CameraRotation rotation, float degrees);
    
    float GetYaw() { return yaw; }
    float GetPitch() { return pitch; }

    void SetPos(glm::vec3& newpos) { pos = newpos; }
    void SetRotation(float newyaw, float newpitch) { yaw = newyaw; pitch = newpitch; };
    void SetFrontVec(glm::vec3& newFrontVec) { frontVec = newFrontVec; }
    void SetUpVec(glm::vec3& newUpVec) { upVec = newUpVec; }
    
    glm::mat4 GetViewMatrix();
};
