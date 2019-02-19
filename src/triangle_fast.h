#ifndef TRIANGLE_FAST_H_
#define TRIANGLE_FAST_H_

#include <glm/glm.hpp>
#include "triangle.h"
#include "ray.h"
#include "intersection_record.h"

class Fast_Triangle : public Triangle
{
    glm::vec3 edge1, edge2;

public:
    Fast_Triangle();
    Fast_Triangle(const glm::vec3 &v1,
                  const glm::vec3 &v2,
                  const glm::vec3 &v3);

    bool intersect(const Ray &ray, IntersectionRecord &ir) const;

};

#endif
