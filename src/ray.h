#pragma once

#include <glm/glm.hpp>

class Ray {
public:
    Ray();

    Ray(const glm::vec3 &origin,
         const glm::vec3 &direction);

    glm::vec3 origin_;
    glm::vec3 direction_;
};
