#pragma once

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Sphere : public Primitive {
public:
    Sphere();
    Sphere(const glm::vec3 &center,
           float radius);

    bool intersect(const Ray &ray,
                   IntersectionRecord &ir) const;

    glm::vec3 center_;
    float radius_;

private:
    static const float kIntersectionTestEpsilon_;
};
