#ifndef TRIANGLE_NAIVE_H_
#define TRIANGLE_NAIVE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "ray.h"
#include "intersection_record.h"

class Naive_Triangle : public Primitive
{
    glm::vec3 vertices[3];

public:
    Naive_Triangle();
    Naive_Triangle(const glm::vec3 &v1,
	     const glm::vec3 &v2,
	     const glm::vec3 &v3);

    bool intersect(const Ray &ray, IntersectionRecord &ir) const;

};

#endif
