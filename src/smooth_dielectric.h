#pragma once

#include "material.h"

class SmoothDielectric : public Material {
public:
    SmoothDielectric(const glm::vec3 &r, const glm::vec3 &e);
    glm::vec3 fr(const glm::vec3 &wi);
    float p();
    glm::vec3 getDirection(const glm::vec3 &dir,
                           const glm::vec3 &normal,
                           float &dot);
};
