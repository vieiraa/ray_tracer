#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include <vector>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Triangle : public Primitive {
    std::vector<glm::vec3> vertices;
    glm::vec3 edge1, edge2;
    glm::vec3 normal;
    glm::vec2 uv;

public:
    Triangle();
    Triangle(const glm::vec3 &v1,
	     const glm::vec3 &v2,
	     const glm::vec3 &v3);

    void setNormal(glm::vec3 n) { normal = n; }
    void setUV(glm::vec2 v) { uv = v; }
    glm::vec3 getNormal() const { return normal; }
    std::vector<glm::vec3> getVertices() const { return vertices; }
    glm::vec3 getEdge1() const { return edge1; }
    glm::vec3 getEdge2() const { return edge2; }
    glm::vec2 getUV() const { return uv; }

    virtual bool intersect(const Ray &ray, IntersectionRecord &ir) const = 0;
};

#endif
