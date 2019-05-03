#pragma once

#include "triangle.h"
#include <vector>
#include <memory>

class TriangleMesh
{
    std::vector<std::unique_ptr<Triangle>> triangles_;
    
public:
    TriangleMesh();
    std::vector<std::unique_ptr<Triangle>>& getTriangles();
    explicit TriangleMesh(const std::string &filename, glm::vec3 color);
    bool loadMesh(const std::string &filename, glm::vec3 color);
    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
};

