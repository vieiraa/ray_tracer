#include "triangle.h"

Triangle::Triangle(const glm::vec3 &v1,
		   const glm::vec3 &v2,
		   const glm::vec3 &v3)
{
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    edge2 = vertices[2] - vertices[0];
    edge1 = vertices[1] - vertices[0];

    //normal = glm::normalize(glm::cross(edge2, edge1));
}

