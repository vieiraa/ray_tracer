#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Triangle : public Primitive {
    glm::vec3 vertices[3];

public:
    Triangle();
    Triangle(const glm::vec3 &v1,
	     const glm::vec3 &v2,
	     const glm::vec3 &v3);

    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
};

#endif
