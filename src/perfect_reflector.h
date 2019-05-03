#pragma once

#include "material.h"
#include "ray.h"
#include <glm/glm.hpp>

class PerfectReflector : public Material
{
public:
    PerfectReflector();
    ~PerfectReflector();

    glm::vec3 fr(const glm::vec3 &wi,
                 const glm::vec3 &wo);

    glm::vec3 getDirection(const Ray &r, const glm::vec3 &normal);
    float p();
};
