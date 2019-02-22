#include "triangle_mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "triangle_fast.h"
#include "triangle_naive.h"
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
	    std::vector<std::pair<glm::vec3, unsigned int>> v;

	    for (int k = 0; k < face.mNumIndices; k++) {
		glm::vec3 aux = glm::vec3(mesh->mVertices[index[k]].x,
					  mesh->mVertices[index[k]].y,
					  mesh->mVertices[index[k]].z);
		v.push_back({aux, index[k]});
	    }

	    Naive_Triangle *t = new Naive_Triangle(v[0].first, v[1].first, v[2].first);
	    glm::vec3 normal = glm::vec3(mesh->mNormals[v[0].second].x,
					 mesh->mNormals[v[1].second].y,
					 mesh->mNormals[v[2].second].z);
	    
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
