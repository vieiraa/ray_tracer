#pragma once

#include "material.h"
#include <glm/glm.hpp>
#include "ray.h"

class Diffuse : public Material {
public:
    Diffuse(glm::vec3 r, glm::vec3 e);
    ~Diffuse();

    glm::vec3 fr(const glm::vec3 &wi);
    float p();
    glm::vec3 getDirection(const glm::vec3 &dir,
                           const glm::vec3 &normal,
                           float &dot);
};
