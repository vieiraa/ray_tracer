#pragma once

#include "material.h"
#include "ray.h"
#include <glm/glm.hpp>

class PerfectReflector : public Material {
public:
    PerfectReflector();
    explicit PerfectReflector(const glm::vec3 &r);
    ~PerfectReflector();

    glm::vec3 fr(const glm::vec3 &wi);
    glm::vec3 getDirection(const glm::vec3 &dir,
                           const glm::vec3 &normal,
                           float &dot);
    float p();
};
