#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Triangle : public Primitive {
public:
    std::vector<glm::vec3> vertices_;
    glm::vec3 edge1_, edge2_;
    glm::vec3 normal_;

    Triangle();
    Triangle(const glm::vec3 &v1,
	     const glm::vec3 &v2,
	     const glm::vec3 &v3);
    
    virtual bool intersect(const Ray &ray, IntersectionRecord &ir) const = 0;
};

