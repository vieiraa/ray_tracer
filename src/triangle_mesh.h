#ifndef TRIANGLE_MESH_H_
#define TRIANGLE_MESH_H_

#include "triangle.h"
#include <vector>

class TriangleMesh
{
    std::vector<Triangle *> triangles_;
    
public:
    TriangleMesh();
    std::vector<Triangle *> getTriangles();
    explicit TriangleMesh(const std::string &filename);
    bool loadMesh(const std::string &filename);
    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
};

#endif
