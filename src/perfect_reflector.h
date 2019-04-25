#pragma once

#include "material.h"
#include "ray.h"
#include <glm/glm.hpp>

class Perfect_reflector : public Material
{
public:
    Perfect_reflector(glm::vec3 r, glm::vec3 e);
    ~Perfect_reflector();

    glm::vec3 fr();

    glm::vec3 getDirection(Ray r);

    int diracDelta(float in, float out);
};