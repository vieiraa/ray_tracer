#pragma once

#include <glm/glm.hpp>
#include "triangle.h"
#include "ray.h"
#include "intersection_record.h"

class Fast_Triangle : public Triangle
{
public:
    Fast_Triangle();
    Fast_Triangle(const glm::vec3 &v1,
                  const glm::vec3 &v2,
                  const glm::vec3 &v3);

    bool intersect(const Ray &ray, IntersectionRecord &ir) const;

};

