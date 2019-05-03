#pragma once

#include <glm/glm.hpp>
#include "brdf.h"
#include "random.h"
#include "ray.h"

class Material {
public:
    Material() = default;
    Material(glm::vec3 r, glm::vec3 e);

    //BRDF *brdf;

    virtual glm::vec3 fr() = 0;
    virtual float p() = 0;
    virtual glm::vec3 getDirection(Ray r) = 0;
    glm::vec3 reflected_;
    glm::vec3 emitted_;

protected:
    Random random;
};
