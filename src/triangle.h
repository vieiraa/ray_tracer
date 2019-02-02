#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "ray.h"
#include "intersection_record.h"

class Triangle : public Primitive
{
    glm::vec3 vertices[3];
    struct {
	float n_u;
	float n_v;
	float n_d;
	int k;

	float b_nu;
	float b_nv;
	float b_d;
	int pad;

	float c_nu;
	float c_nv;
	float c_d;
	int pad2;
    } acc;

public:
    Triangle();
    Triangle(const glm::vec3 &v1,
	     const glm::vec3 &v2,
	     const glm::vec3 &v3);

    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
};

#endif
