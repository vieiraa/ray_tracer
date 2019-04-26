#include "triangle.h"

Triangle::Triangle(const glm::vec3 &v1,
		   const glm::vec3 &v2,
		   const glm::vec3 &v3)
{
    vertices_.push_back(v1);
    vertices_.push_back(v2);
    vertices_.push_back(v3);
    edge2_ = vertices_[2] - vertices_[0];
    edge1_ = vertices_[1] - vertices_[0];

    normal_ = glm::normalize(glm::cross(edge2_, edge1_));
}

void Triangle::computeBounds(const glm::vec3 &plane_normal, float &near, float &far) const {
    for (auto &v : vertices_) {
        float d = glm::dot(plane_normal, v);
        if (d < near)
            near = d;
        if (d > far)
            far = d;
    }
}
