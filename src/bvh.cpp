#include "bvh.h"
#include <iostream>

static const float sqrt3 = glm::sqrt(3) / 3.0f;
static const glm::vec3 planes_normals_[] = {
    glm::vec3(1, 0, 0),
    glm::vec3(0, 1, 0),
    glm::vec3(0, 0, 1),
    glm::vec3(sqrt3, sqrt3, sqrt3),
    glm::vec3(-sqrt3, sqrt3, sqrt3),
    glm::vec3(-sqrt3, -sqrt3, sqrt3),
    glm::vec3(sqrt3, -sqrt3, sqrt3)
};

std::ostream& operator<<(std::ostream &os, const glm::vec3 &vec) {
    os << "x = " << vec.x << ", y = " << vec.y << ", z = " << vec.z;

    return os;
}

BVH::BVH(std::vector<Primitive*> &primitives) :
    primitives_(primitives)
{
    BoundingVolume volume;
    volumes_.resize(primitives_.size(), BVH::BoundingVolume());

    for (unsigned i = 0; i < primitives_.size(); i++) {
        for (unsigned j = 0; j < num_planes; j++) {
            primitives_[i]->computeBounds(planes_normals_[j],
                                          volumes_[i].dnear[j],
                                          volumes_[i].dfar[j]);
        }

        volume.extendBy(volumes_[i]);
        //volume.primitive = primitives_[i];
        volumes_[i].primitive = primitives_[i];
    }

    octree = new Octree(volume);

    for (auto &v : volumes_) {
        octree->insert(&v);
    }

    octree->build();
}

bool BVH::intersect(const Ray &ray, IntersectionRecord &ir) const {
    bool hit = false;
    float inf = std::numeric_limits<float>::infinity();
    float numerators[num_planes];
    float denominators[num_planes];
    for (unsigned i = 0; i < num_planes; i++) {
        numerators[i] = glm::dot(planes_normals_[i], ray.origin_);
        denominators[i] = glm::dot(planes_normals_[i], ray.direction_);
    }

    float near = -inf, far = inf;
    if (!octree->root->volume.intersect(near, far, numerators, denominators) ||
        (far < 0))
    {
        return false;
    }

    std::priority_queue<BVH::Octree::QueueElement> queue;
    queue.push(BVH::Octree::QueueElement(octree->root, 0));
    while (!queue.empty() && (queue.top().t < ir.t_)) {
        const OctreeNode *node = queue.top().node;
        queue.pop();
        if (node->is_leaf) {
            for (auto &p : node->data) {
                IntersectionRecord temp_ir;
                temp_ir.t_ = std::numeric_limits<float>::infinity();
                if (p->primitive->intersect(ray, temp_ir) && (temp_ir.t_ < ir.t_) && (temp_ir.t_ > 0.0f)) {
                    ir = temp_ir;
                    hit = true;
                }
            }
        }

        else {
            for (unsigned i = 0; i < 8; i++) {
                if (node->children[i]) {
                    float near_child = -inf, far_child = inf;
                    if (node->children[i]->volume.intersect(near_child, far_child, numerators, denominators)) {
                        float t = (near_child < 0 && far_child >= 0) ? far_child : near_child;
                        queue.push(BVH::Octree::QueueElement(node->children[i], t));
                    }
                }
            }
        }
    }

    return hit;
}

BVH::BoundingVolume::BoundingVolume() : primitive(nullptr) {
    float inf = std::numeric_limits<float>::infinity();

    dnear.fill(inf);
    dfar.fill(-inf);
}

void BVH::BoundingVolume::extendBy(const BoundingVolume &v) {
    for (unsigned i = 0; i < num_planes; i++) {
        if (v.dnear[i] < dnear[i])
            dnear[i] = v.dnear[i];
        if (v.dfar[i] > dfar[i])
            dfar[i] = v.dfar[i];
    }
}

bool BVH::BoundingVolume::intersect(float &near,
                                    float &far,
                                    float *numerators,
                                    float *denominators) const
{
    for (unsigned i = 0; i < num_planes; i++) {
        float tn = (dnear[i] - numerators[i]) / denominators[i];
        float tf = (dfar[i] - numerators[i]) / denominators[i];

        if (denominators[i] < 0) {
            std::swap(tn, tf);
        }

        if (tn > near)
            near = tn;

        if (tf < far)
            far = tf;

        if (near > far)
            return false;
    }

    return true;
}

inline glm::vec3 BVH::BoundingVolume::centroid() const {
    return glm::vec3((dnear[0] + dfar[0]) * 0.5f,
                     (dnear[1] + dfar[1]) * 0.5f,
                     (dnear[2] + dfar[2]) * 0.5f);
}

BVH::OctreeNode::OctreeNode() : is_leaf(true) {
    children.fill(nullptr);
}

BVH::Octree::Octree(BVH::BoundingVolume &v) {
    float xdiff = v.dfar[0] - v.dnear[0];
    float ydiff = v.dfar[1] - v.dnear[1];
    float zdiff = v.dfar[2] - v.dnear[2];

    float max_dif = glm::max(xdiff, glm::max(ydiff, zdiff));
    glm::vec3 aux(v.dnear[0] + v.dfar[0],
                  v.dnear[1] + v.dfar[1],
                  v.dnear[2] + v.dfar[2]);
    bounds[0] = (aux - max_dif) * 0.5f;
    bounds[1] = (aux + max_dif) * 0.5f;
    root = new BVH::OctreeNode();
}

void BVH::Octree::insert(const BoundingVolume *volume) {
    insert(root, volume, bounds[0], bounds[1], 0);
}

void BVH::Octree::build() {
    build(root, bounds[0], bounds[1]);
}

void BVH::Octree::insert(BVH::OctreeNode *n,
                         const BoundingVolume *v,
                         glm::vec3 &b_min,
                         glm::vec3 &b_max, int depth)
{

    if (n->is_leaf) {
        if (!n->data.size() || depth == 16)
            n->data.push_back(v);

        else {
            n->is_leaf = false;
            while (n->data.size()) {
                insert(n, n->data.back(), b_min, b_max, depth);
                n->data.pop_back();
            }
            insert(n, v, b_min, b_max, depth);
        }
    }

    else {
        glm::vec3 vol_centroid = v->centroid();
        glm::vec3 node_centroid = (b_max + b_min) * 0.5f;

        unsigned child_index = 0;
        glm::vec3 child_b_min, child_b_max;
        if (vol_centroid.x > node_centroid.x) {
            child_index = 4;
            child_b_min.x = node_centroid.x;
            child_b_max.x = b_max.x;
        }

        else {
            child_b_min.x = b_min.x;
            child_b_max.x = node_centroid.x;
        }

        if (vol_centroid.y > node_centroid.y) {
            child_index += 2;
            child_b_min.y = node_centroid.y;
            child_b_max.y = b_max.y;
        }

        else {
            child_b_min.y = b_min.y;
            child_b_max.y = node_centroid.y;
        }

        if (vol_centroid.z > node_centroid.z) {
            child_index += 1;
            child_b_min.z = node_centroid.z;
            child_b_max.z = b_max.z;
        }

        else {
            child_b_min.z = b_min.z;
            child_b_max.z = node_centroid.z;
        }

        if (!n->children[child_index])
            n->children[child_index] = new BVH::OctreeNode();

        insert(n->children[child_index], v, child_b_min, child_b_max, depth + 1);
    }
}

void BVH::Octree::computeChildBound(const unsigned i,
                                    const glm::vec3 &centroid,
                                    const glm::vec3 &b_min,
                                    const glm::vec3 &b_max,
                                    glm::vec3 &p_min,
                                    glm::vec3 &p_max) const
{
    p_min.x = (i & 4) ? centroid.x : b_min.x;
    p_max.x = (i & 4) ? b_max.x : centroid.x;
    p_min.y = (i & 2) ? centroid.y : b_min.y;
    p_max.y = (i & 2) ? b_max.y : centroid.y;
    p_min.z = (i & 1) ? centroid.z : b_min.z;
    p_max.z = (i & 1) ? b_max.z : centroid.z;
}

void BVH::Octree::build(BVH::OctreeNode *node,
                        const glm::vec3 &b_min,
                        const glm::vec3 &b_max)
{
    if (node->is_leaf) {
        for (unsigned i = 0; i < node->data.size(); i++)
            node->volume.extendBy(*node->data[i]);
    }

    else {
        for (unsigned i = 0; i < 8; i++) {
            if (node->children[i]) {
                glm::vec3 child_b_min, child_b_max;
                glm::vec3 b_centroid = (b_min + b_max) * 0.5f;
                computeChildBound(i, b_centroid, b_min, b_max, child_b_min, child_b_max);
                build(node->children[i], child_b_min, child_b_max);
                node->volume.extendBy(node->children[i]->volume);
            }
        }
    }
}

BVH::Octree::QueueElement::QueueElement(const BVH::OctreeNode *n,
                                        float hit)
    : node(n), t(hit) {}

bool operator<(const BVH::Octree::QueueElement &a,
               const BVH::Octree::QueueElement &b)
{
    return a.t > b.t;
}
