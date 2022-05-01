#pragma once

#include <glm/glm.hpp>

class Ray {
private:
    glm::vec3 position;
    glm::vec3 direction;
public:
    Ray(glm::vec3& position, glm::vec3& direction) :position(position), direction(direction) {}
     
    void Advance(float amount);
    glm::vec3& GetPos() { return position; }
};
