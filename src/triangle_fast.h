#ifndef TRIANGLE_FAST_H_
#define TRIANGLE_FAST_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "ray.h"
#include "intersection_record.h"

class Fast_Triangle : public Primitive
{
    glm::vec3 vertices[3];

public:
    Fast_Triangle();
    Fast_Triangle(const glm::vec3 &v1,
                  const glm::vec3 &v2,
                  const glm::vec3 &v3);

    bool intersect(const Ray &ray, IntersectionRecord &ir) const;

};

#endif
