#pragma once

#include <glm/glm.hpp>
#include "triangle.h"
#include "ray.h"
#include "intersection_record.h"
#include "aabb.h"

class FastTriangle : public Triangle {
public:
    FastTriangle();
    FastTriangle(const glm::vec3 &v1,
                 const glm::vec3 &v2,
                 const glm::vec3 &v3);

    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
};
