#ifndef TRIANGLE_MESH_H_
#define TRIANGLE_MESH_H_

#include "primitive.h"
#include "triangle.h"
#include <vector>
#include <assimp/scene.h>

class TriangleMesh : public Primitive
{
    std::vector<Triangle> triangles_;
    
public:
    TriangleMesh();
    TriangleMesh(const unsigned int nfaces,
		 const std::vector<unsigned int> &faceIndex,
		 const std::vector<unsigned int> &vertsIndex,
		 const std::vector<glm::vec3> &verts,
		 std::vector<glm::vec3> &normals,
		 std::vector<glm::vec3> &st);
    bool loadMesh(const std::string &filename);
    void initMesh(unsigned int index, const aiMesh *aiMesh);
    bool initMaterials(const aiScene *s, const std::string &filename);
    bool initFromScene(const aiScene *scene, const std::string &filename);
    void clear();
    bool intersect(const Ray &ray, IntersectionRecord &ir);
};

#endif
