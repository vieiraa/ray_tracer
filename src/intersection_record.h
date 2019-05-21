#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "material.h"

struct IntersectionRecord {
    float t_;
    glm::vec3 position_;
    glm::vec3 normal_;
    std::weak_ptr<Material> material_;
};
