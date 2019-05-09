#pragma once

#include "triangle.h"
#include <vector>
#include <memory>

class TriangleMesh
{
    std::vector<Triangle*> triangles_;

public:
    explicit TriangleMesh(std::vector<Triangle*> &t, const char *name);
    std::vector<Triangle*>& getTriangles();

    std::string name_;
};

class Mesh {
    std::vector<TriangleMesh> meshes_;

public:
    explicit Mesh(const std::string &filename);
    bool loadMesh(const std::string &filename);
    std::vector<TriangleMesh> getMeshes();
};
