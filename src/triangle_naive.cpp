#include "triangle_naive.h"

Naive_Triangle::Naive_Triangle(const glm::vec3 &v1,
		   const glm::vec3 &v2,
		   const glm::vec3 &v3)
    : Triangle(v1, v2, v3)
{
}

bool Naive_Triangle:: intersect(const Ray &ray, IntersectionRecord &ir) const
{
    std::vector<glm::vec3> vertices = getVertices();
    float a = vertices[0].x - vertices[1].x;
    float b = vertices[0].y - vertices[1].y;
    float c = vertices[0].z - vertices[1].z;
    float d = vertices[0].x - vertices[2].x;
    float e = vertices[0].y - vertices[2].y;
    float f = vertices[0].z - vertices[2].z;
    float g = ray.direction_.x;
    float h = ray.direction_.y;
    float i = ray.direction_.z;
    float j = vertices[0].x - ray.origin_.x;
    float k = vertices[0].y - ray.origin_.y;
    float l = vertices[0].z - ray.origin_.z;

    float ei_hf = e * i - h * f;
    float gf_di = g * f - d * i;
    float dh_eg = d * h - e * g;
    float ak_jb = a * k - j * b;
    float jc_al = j * c - a * l;
    float bl_kc = b * l - k * c;

    float M = a * ei_hf + b * gf_di + c * dh_eg;

    float t = -(f * ak_jb + e * jc_al + d * bl_kc) / M;
    if (t < 0.0f)
    	return false;

    float gamma = (i * ak_jb + h * jc_al + g * bl_kc) / M;
    if (gamma < 0.0f || gamma > 1.0f)
	return false;

    float beta = (j * ei_hf + k * gf_di + l * dh_eg) / M;
    if (beta < 0.0f || beta > (1.0f - gamma))
	return false;

    ir.t_ = t;
    ir.position_ = ray.origin_ + ir.t_ * ray.direction_;
    ir.normal_ = glm::normalize(glm::cross(vertices[1] - vertices[0],
					   vertices[2] - vertices[0]));

    return true;
}
