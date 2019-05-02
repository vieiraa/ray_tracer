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

AABB Triangle::getAABB(void) const
{
    AABB aabb;

    aabb.min_ = glm::min(glm::min(vertices_[0], vertices_[1]), vertices_[2]);
    aabb.max_ = glm::max(glm::max(vertices_[0], vertices_[1]), vertices_[2]);
    aabb.centroid_ = (1.0f / 3.0f) * (vertices_[0]+ vertices_[1] + vertices_[2]);
    return aabb;
}

