#ifndef MESH_H_
#define MESH_H_

#include "primitive.h"
#include "triangle.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class TriangleMesh : public Primitive
{
    unsigned int num_tr_;
    
    
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
    void clear();
};

#endif
