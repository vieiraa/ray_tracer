#pragma once

#include <glm/glm.hpp>
#include "ray.h"

class AABB {
public:
    AABB();
    AABB(const glm::vec3 &p1, const glm::vec3 &p2);
    AABB(const glm::vec3 &min, const glm::vec3 &max, const glm::vec3 &centroid);

    glm::vec3 diagonal() const;
    double getArea();
    double getVolume();
    bool intersect(const Ray &ray) const;

    glm::vec3 min_;
    glm::vec3 max_;
    glm::vec3 centroid_;

    AABB operator+(AABB &other) const;
};
