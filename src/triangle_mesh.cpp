#include "triangle_mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "triangle_fast.h"
#include <iostream>

const float KINFINITY = std::numeric_limits<float>::max();
const float EPSILON = 1e-8;

bool TriangleMesh::loadMesh(const std::string &filename) {
    Assimp::Importer importer;
    std::vector<Triangle *> triangles;
    const aiScene *scene = importer.ReadFile(filename,
					     aiProcess_CalcTangentSpace |
					     aiProcess_Triangulate |
					     aiProcess_JoinIdenticalVertices |
					     aiProcess_SortByPType);

    if (!scene)
	std::exit(1);

    for (int i = 0; i < scene->mNumMeshes; i++) {
	aiMesh *mesh = scene->mMeshes[i];

	for (int j = 0; j < mesh->mNumFaces; j++) {
	    aiFace face = mesh->mFaces[j];
	    unsigned int *index = face.mIndices;
	    std::vector<glm::vec3> v;

	    for (int k = 0; k < face.mNumIndices; k++) {
		glm::vec3 aux = glm::vec3(mesh->mVertices[index[k]].x,
					  mesh->mVertices[index[k]].y,
					  mesh->mVertices[index[k]].z);
		v.push_back(aux);
	    }

	    Fast_Triangle *t = new Fast_Triangle(v[0], v[1], v[2]);
	    glm::vec3 normal = glm::vec3(mesh->mNormals[i].x,
					 mesh->mNormals[i].y,
					 mesh->mNormals[i].z);
	    t->setNormal(normal);
	    triangles.push_back(t);
	}
    }

    triangles_ = triangles;
    
    return true;
}

TriangleMesh::TriangleMesh(const std::string &filename) {
    loadMesh(filename);
}

TriangleMesh::TriangleMesh() = default;

std::vector<Triangle *> TriangleMesh::getTriangles() {
    return triangles_;
}
