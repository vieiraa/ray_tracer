#pragma once

#include <array>
#include <vector>
#include <queue>
#include "primitive.h"

static const unsigned num_planes = 7;

class BVH {
public:
    struct BoundingVolume;
    struct OctreeNode;
    struct Octree;

private:
    //std::array<glm::vec3, num_planes> planes_normals_;
    std::vector<Primitive*> &primitives_;

    std::vector<BoundingVolume> volumes_;
    Octree *octree;

public:
    explicit BVH(std::vector<Primitive*> &primitives);
    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
};

struct BVH::BoundingVolume {
    Primitive *primitive;
    std::array<float, num_planes> dnear;
    std::array<float, num_planes> dfar;

    BoundingVolume();
    void extendBy(const BoundingVolume &b);
    bool intersect(float &near, float &far, unsigned &plane_index) const;
    glm::vec3 centroid() const;
};

struct BVH::OctreeNode {
    std::array<OctreeNode*, 8> children;
    std::vector<const BoundingVolume *> data;
    BoundingVolume volume;
    bool is_leaf;

    OctreeNode();
};

struct BVH::Octree {
    OctreeNode *root;
    std::array<glm::vec3, 2> bounds;

    explicit Octree(BoundingVolume &volume);

    void insert(const BoundingVolume *volume);
    void build();

    struct QueueElement {
        const OctreeNode *node;
        float t;

        QueueElement(const OctreeNode *n, float hit);

        friend bool operator<(const QueueElement &a, const QueueElement &b);
    };

private:
    void insert(OctreeNode *root, const BoundingVolume *volume,
                glm::vec3 &b_min, glm::vec3 &b_max, int depth);
    void computeChildBound(const unsigned i, const glm::vec3 &centroid,
                           const glm::vec3 &b_min, const glm::vec3 &b_max,
                           glm::vec3 &p_min, glm::vec3 &p_max) const;
    void build(OctreeNode *node,
               const glm::vec3 &b_min,
               const glm::vec3 &b_max);
};
