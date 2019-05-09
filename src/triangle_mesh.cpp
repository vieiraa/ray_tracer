#include "triangle_mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "triangle_fast.h"
#include "triangle_naive.h"
#include "diffuse.h"
#include "perfect_reflector.h"
#include <iostream>

#ifdef __MINGW32__
#include <time.h>
double drand48() {
    static bool first = true;

    if (first) {
        srand((long) time(NULL));
        first = false;
    }

    return (double)rand() / RAND_MAX;
}
#endif

const float KINFINITY = std::numeric_limits<float>::max();
const float EPSILON = 1e-8;

Mesh::Mesh(const std::string &filename) {
    loadMesh(filename);
}

std::vector<TriangleMesh> Mesh::getMeshes() {
    return meshes_;
}

bool Mesh::loadMesh(const std::string &filename) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename,
					     aiProcess_CalcTangentSpace |
					     aiProcess_Triangulate |
					     aiProcess_JoinIdenticalVertices |
					     aiProcess_SortByPType);

    if (!scene) {
        std::cerr << "File " << filename << " not found.\nExiting...\n";
	std::exit(1);
    }

    for (int i = 0; i < scene->mNumMeshes; i++) {
	aiMesh *mesh = scene->mMeshes[i];
        std::vector<Triangle*> triangles;

	for (int j = 0; j < mesh->mNumFaces; j++) {
	    aiFace face = mesh->mFaces[j];
	    unsigned int *index = face.mIndices;
	    std::vector<std::pair<glm::vec3, unsigned int>> v;
            glm::vec3 normal;

	    for (int k = 0; k < face.mNumIndices; k++) {
		glm::vec3 aux = glm::vec3(mesh->mVertices[index[k]].x,
					  mesh->mVertices[index[k]].y,
					  mesh->mVertices[index[k]].z);
		v.push_back({aux, index[k]});
                normal = glm::vec3(mesh->mNormals[index[k]].x,
                                   mesh->mNormals[index[k]].y,
                                   mesh->mNormals[index[k]].z);
	    }

            Triangle *t = new FastTriangle(v[0].first, v[1].first, v[2].first);

            if (mesh->HasNormals())
                t->normal_ = normal;

	    triangles.push_back(t);
	}

        meshes_.push_back(TriangleMesh(triangles, mesh->mName.C_Str()));
    }



    return true;
}

TriangleMesh::TriangleMesh(std::vector<Triangle*> &tr, const char *name) :
    triangles_(std::move(tr)), name_(name)
{}

std::vector<Triangle*>& TriangleMesh::getTriangles() {
    return triangles_;
}
