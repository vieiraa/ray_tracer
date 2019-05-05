#pragma once

#include "material.h"
#include "ray.h"
#include <glm/glm.hpp>

class PerfectReflector : public Material
{
public:
    PerfectReflector();
    PerfectReflector(const glm::vec3 &r);
    ~PerfectReflector();

    glm::vec3 fr(const glm::vec3 &wi,
                 const glm::vec3 &wo);

    glm::vec3 getDirection(const Ray &r, IntersectionRecord &ir);
    glm::vec3 get_reflected_direction(const Ray &wi, const glm::vec3 &normal);
    
    float p();
};
