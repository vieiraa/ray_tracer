#pragma once

#include <glm/glm.hpp>
#include "brdf.h"

class Material {
public:
    Material() = default;
    Material(glm::vec3 r, glm::vec3 e);
    
    //BRDF *brdf;
    glm::vec3 reflected_;
    glm::vec3 emitted_;
};
