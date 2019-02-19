#include "triangle_mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

bool TriangleMesh::loadMesh(const std::string &filename) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename,
					     aiProcess_CalcTangentSpace |
					     aiProcess_Triangulate |
					     aiProcess_JoinIdenticalVertices |
					     aiProcess_SortByPType);

    if (!scene)
	std::exit(1);

    return initFromScene(scene, filename);
}

void TriangleMesh::initMesh(unsigned int index, const aiMesh *mesh) {
    
}

bool intersect(const Ray &ray, IntersectionRecord &ir) {
    
}
