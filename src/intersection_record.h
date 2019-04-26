#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>
#include <memory>
#include "material.h"

struct IntersectionRecord
{
    float t_;
    glm::vec3 position_;
    glm::vec3 normal_;
    std::weak_ptr<Material> material_;

    IntersectionRecord& operator=(IntersectionRecord &ir) {
        t_ = ir.t_;
        position_ = ir.position_;
        normal_ = ir.normal_;
        material_ = std::move(ir.material_);

        return *this;
    }
};

#endif /* INTERSECTION_RECORD_H_ */
