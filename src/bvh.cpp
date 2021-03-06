#include "bvh.h"
#include "aabb.h"

BVH_SAH::BVH_SAH(const std::vector<Primitive::PrimitiveUniquePtr> &primitives) :
    primitives_(primitives)
{
    if (primitives_.size() > 0) {
        std::deque< PrimitiveAABBArea > s(primitives_.size());
        primitive_id_.resize(primitives_.size());

        AABB root_aabb;

        for (std::size_t i = 0; i < primitives_.size(); i++) {
            AABB aabb = primitives_[i]->getAABB();

            // compute the AABB area for the root node
            if (!i)
                root_aabb = aabb;
            else
                root_aabb = root_aabb + aabb;

            s[i].primitive_id_ = i;
            s[i].centroid_ = aabb.centroid_;
            s[i].aabb_ = aabb;
        }

        splitNode(&root_node_, s, 0, s.size() - 1, root_aabb.getArea());
    }
}

BVH_SAH::~BVH_SAH() {
    if (root_node_) {
        delete root_node_;
        root_node_ = nullptr;
    }
}

bool BVH_SAH::intersect(const Ray &ray,
                        IntersectionRecord &ir,
                        unsigned int &num_intersection_tests_,
                        unsigned int &num_intersections_) const
{
    return traverse(root_node_, ray, ir, num_intersection_tests_, num_intersections_);
}

float BVH_SAH::SAH(std::size_t s1_size,
                   float s1_area,
                   std::size_t s2_size,
                   float s2_area,
                   float s_area)
{
    if ((s2_area == std::numeric_limits< float >::infinity()) && (s2_size == 0))
        return std::numeric_limits< float >::infinity();

    return 2.0f * cost_intersec_aabb_ + ((s1_area / s_area) * s1_size * cost_intersec_tri_) +
        ((s2_area / s_area) * s2_size * cost_intersec_tri_);
}

/* BVH construction based on the algorithm presented in the paper:
 *
 *     "Ray Tracing Deformable Scenes Using Dynamic Bounding Volume Hierarchies".
 *     Ingo Wald, Solomon Boulos, and Peter Shirley
 *     ACM Transactions on Graphics.
 *     Volume 26 Issue 1, 2007.
 */
void BVH_SAH::splitNode(BVHNode **node,
                        std::deque< PrimitiveAABBArea > &s,
                        std::size_t first,
                        std::size_t last,
                        float s_area)
{
    (*node) = new BVHNode();
    (*node)->first_ = first;
    (*node)->last_ = last;
    (*node)->left_ = nullptr;
    (*node)->right_ = nullptr;

    std::deque< PrimitiveAABBArea > s_aux;

    float best_cost = cost_intersec_tri_ * (last + 1 - first);
    int best_axis = -1;
    int best_event = -1;

    for (int axis = 1; axis <= 3; axis++) {
        switch (axis) {
        case 1:
            std::sort(s.begin() + first, s.begin() + last + 1, Comparator::sortInX);
            break;
        case 2:
            std::sort(s.begin() + first, s.begin() + last + 1, Comparator::sortInY);
            break;
        case 3:
            std::sort(s.begin() + first, s.begin() + last + 1, Comparator::sortInZ);
            break;
        }

        s_aux = std::deque< PrimitiveAABBArea >(s.begin() + first, s.begin() + last + 1);

        for (unsigned i = first; i <= last; i++) {
            if (i == first) {
                s[i].left_area_ = std::numeric_limits< float >::infinity();
                s_aux[0].left_aabb_ = s_aux[0].aabb_;
            } else {
                s[i].left_area_ = s_aux[i - first - 1].left_aabb_.getArea();
                s_aux[i - first].left_aabb_ = s_aux[i - first].aabb_ + s_aux[i - first - 1].left_aabb_;
            }
        }

        for (int i = last; i >= static_cast<int>(first); i--) {
            if (i == static_cast<int>(last)) {
                s[i].right_area_ = std::numeric_limits< float >::infinity();
                s_aux[last - first].right_aabb_ = s_aux[last - first].aabb_;
            } else {
                s[i].right_area_ = s_aux[i - first + 1].right_aabb_.getArea();
                s_aux[i - first].right_aabb_ = s_aux[i - first].aabb_ + s_aux[i - first + 1].right_aabb_;
            }

            float this_cost = SAH(i - first + 1,
                                  s[i].left_area_,
                                  last - i,
                                  s[i].right_area_,
                                  s_area);

            if (this_cost < best_cost) {
                best_cost = this_cost;
                best_event = i;
                best_axis = axis;
            }
        }
    }

    if (best_axis == -1) { // This is a leaf node
        primitives_inserted_ += last - first + 1;

        for (unsigned i = first; i <= last; i++) {
            primitive_id_[i] = s[i].primitive_id_;

            if (i == first)
                (*node)->aabb_ = s[i].aabb_;
            else
                (*node)->aabb_ = (*node)->aabb_ + s[i].aabb_;
        }
    } else { // This is an inner node
        // Make inner node with best_axis / best_event
        switch (best_axis) {
        case 1:
            std::sort(s.begin() + first, s.begin() + last + 1, Comparator::sortInX);
            break;
        case 2:
            std::sort(s.begin() + first, s.begin() + last + 1, Comparator::sortInY);
            break;
        case 3:
            std::sort(s.begin() + first, s.begin() + last + 1, Comparator::sortInZ);
            break;
        }

        splitNode(&(*node)->left_, s, first, best_event, s_area);
        splitNode(&(*node)->right_, s, best_event + 1, last, s_area);

        (*node)->aabb_ = (*node)->left_->aabb_ + (*node)->right_->aabb_;
    }
}

bool BVH_SAH::traverse(const BVHNode *node,
                       const Ray &ray,
                       IntersectionRecord &ir,
                       unsigned int &num_intersection_tests_,
                       unsigned int &num_intersections_) const
{
    bool primitive_intersect = false;

    if (node) {
        num_intersection_tests_++;

        if (node->aabb_.intersect(ray)) {
            num_intersections_++;

            if ((!node->left_) && (!node->right_)) { // is a leaf node
                IntersectionRecord tmp_ir;

                for (unsigned i = node->first_; i <= node->last_; i++) {
                    num_intersection_tests_++;

                    if (primitives_[primitive_id_[i]]->intersect(ray, tmp_ir)) {
                        num_intersections_++;

                        if ((tmp_ir.t_ < ir.t_) && (tmp_ir.t_ > 0.0f)) {
                            ir = tmp_ir;
                            primitive_intersect = true;
                        }
                    }
                }
            } else {
                if (traverse(node->left_, ray, ir, num_intersection_tests_, num_intersections_))
                    primitive_intersect = true;

                if (traverse(node->right_, ray, ir, num_intersection_tests_, num_intersections_))
                    primitive_intersect = true;
            }
        }
    }

    return primitive_intersect;
}

unsigned BVH_SAH::height(BVHNode *node) const {
    if (!node)
        return 0;

    return 1 + glm::max(height(node->left_), height(node->right_));
}

BVH_SAH::BVHNode* BVH_SAH::getRoot() const {
    return root_node_;
}
