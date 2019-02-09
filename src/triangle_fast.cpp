#include "triangle_fast.h"

Fast_Triangle::Fast_Triangle(const glm::vec3 &v1,
		   const glm::vec3 &v2,
		   const glm::vec3 &v3)
{
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;

    edge1 = vertices[1] - vertices[0];
    edge2 = vertices[2] - vertices[0];
    
    normal = glm::normalize(glm::cross(edge1, edge2));
}

bool Fast_Triangle::intersect(const Ray &ray, IntersectionRecord &ir) const
{
    glm::vec3 aux, p, q;
    float det;
    float u, v, t;

    p = glm::cross(ray.direction_, edge2);
    det = glm::dot(edge1, p);

    if (det > -0.000001f && det < 0.000001f)
	return false;

    det = 1.0f / det;

    aux = ray.origin_ - vertices[0];

    u = glm::dot(aux, p) * det;
    if (u < 0.0f || u > 1.0f)
	return false;

    q = glm::cross(aux, edge1);

    v = glm::dot(ray.direction_, q) * det;
    if (v < 0.0f || (u + v) > 1.0f)
	return false;

    t = glm::dot(edge2, q) * det;

    ir.t_ = t;
    ir.position_ = ray.origin_ + ir.t_ * ray.direction_;
    ir.normal_ = normal;

    return true;
}
