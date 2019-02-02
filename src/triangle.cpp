#include "triangle.h"

#define KU modulo[acc.k + 1]
#define KV modulo[acc.k + 2]

unsigned int modulo[] = {0, 1, 2, 0, 1};

Triangle::Triangle(const glm::vec3 &v1,
		   const glm::vec3 &v2,
		   const glm::vec3 &v3)
{
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;

    glm::vec3 b = vertices[2] - vertices[0];
    glm::vec3 c = vertices[1] - vertices[0];

    glm::vec3 normal = glm::cross(c, b);

    glm::vec3 aux = glm::abs(normal);
    if (aux.x > aux.y) {
	if (aux.x > aux.z)
	    acc.k = 0;
	else
	    acc.k = 2;
    } else if (aux.y > aux.z)
	acc.k = 1;
    else
	acc.k = 2;

    normal /= normal[acc.k];
    acc.n_u = normal[modulo[acc.k + 1]];
    acc.n_v = normal[modulo[acc.k + 2]];
    acc.n_d = glm::dot(vertices[0], normal);
    
    float temp = b.x * c.y - b.y * c.x;
    acc.b_nu = -b.y / temp;
    acc.b_nv = b.x / temp;
    acc.b_d = (b.y * vertices[0].x - b.x * vertices[0].y) / temp;

    acc.c_nu = c.y / temp;
    acc.c_nv = -c.x / temp;
    acc.c_d = (c.x * vertices[0].y - c.y * vertices[0].x) / temp;
}

bool Triangle::intersect(const Ray &ray, IntersectionRecord &ir) const
{
    float nd = 1.0f /
	(ray.direction_[acc.k] + acc.n_u * ray.direction_[KU] +
	 acc.n_v * ray.direction_[KV]);

    float t = (acc.n_d - ray.origin_[acc.k] -
		     acc.n_u * ray.origin_[KU] -
		     acc.n_v * ray.origin_[KV]) * nd;

    if (!(ir.t_ > t && t > 0.000001f))
	return false;

    float hu = ray.origin_[KU] + t * ray.direction_[KU];
    float hv = ray.origin_[KV] + t * ray.direction_[KV];

    float beta = hu * acc.b_nu + hv * acc.b_nv + acc.b_d;
    if (beta < 0.0f)
	return false;

    float gamma = hu * acc.c_nu + hv * acc.c_nv + acc.c_d;
    if (gamma < 0.0f)
	return false;

    if ((beta + gamma) > 1.0f)
	return false;
    
    ir.t_ = t;
    ir.position_ = ray.origin_ + ir.t_ * ray.direction_;
    ir.normal_ = glm::vec3(beta, gamma, 1);

    return true;
}
