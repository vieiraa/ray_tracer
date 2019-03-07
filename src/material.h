#pragma once

#include <glm/glm.hpp>

class Material {
public:
    Material() = default;
    Material(glm::vec3 r, glm::vec3 e);
    
    glm::vec3 reflected_;
    glm::vec3 emitted_;
};
