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
    explicit TriangleMesh(const std::string &filename);
    bool loadMesh(const std::string &filename);
    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
};
