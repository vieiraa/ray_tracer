#pragma once

#include <glm/glm.hpp>
#include "random.h"
#include "ray.h"

class Material {
public:
    Material() = default;
    Material(glm::vec3 r, glm::vec3 e);

    virtual glm::vec3 fr(const glm::vec3 &wi) = 0;
    virtual float p() = 0;
    virtual glm::vec3 getDirection(const glm::vec3 &dir,
                                   const glm::vec3 &normal,
                                   float &dot) = 0;

    glm::vec3 reflected_;
    glm::vec3 emitted_;

protected:
    Random random;
};
