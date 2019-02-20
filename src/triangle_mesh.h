#ifndef TRIANGLE_MESH_H_
#define TRIANGLE_MESH_H_

#include "primitive.h"
#include "triangle.h"
#include <vector>

class TriangleMesh : public Primitive
{
    std::vector<Triangle *> triangles_;
    
public:
    TriangleMesh();
    explicit TriangleMesh(const std::string &filename);
    bool loadMesh(const std::string &filename);
    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
};

#endif
