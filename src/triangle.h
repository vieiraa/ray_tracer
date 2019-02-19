#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Triangle : public Primitive {
    glm::vec3 vertices[3];
    glm::vec3 normal;

public:
    Triangle();
    Triangle(const glm::vec3 &v1,
	     const glm::vec3 &v2,
	     const glm::vec3 &v3);

    void setNormal(glm::vec3 n) { normal = n; }
    glm::vec3* getVertices() { return vertices; }
    glm::vec3 getNormal() { return normal; }

    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
};

#endif
