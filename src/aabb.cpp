#include "aabb.h"
#include "ray.h"

AABB::AABB() {};

AABB::AABB(const glm::vec3 &p1, const glm::vec3 &p2) {
    min_ = glm::vec3(glm::min(p1.x, p2.x), glm::min(p1.y, p2.y), glm::min(p1.z, p2.z));
    max_ = glm::vec3(glm::max(p1.x, p2.x), glm::max(p1.y, p2.y), glm::max(p1.z, p2.z));
};

AABB::AABB(const glm::vec3 &min, const glm::vec3 &max, const glm::vec3 &centroid) :
    min_(min),
    max_(max),
    centroid_(centroid)
{}

glm::vec3 AABB::diagonal() const {
    return max_ - min_;
}

double AABB::getArea() {
    glm::vec3 d = diagonal();
    return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
}

double AABB::getVolume() {
    glm::vec3 d = diagonal();
    return d.x * d.y * d.z;
}

bool AABB::intersect(const Ray &ray) const {
    float txmin;
    float txmax;
    float tymin;
    float tymax;
    float tzmin;
    float tzmax;
    float divx;
    float divy;
    float divz;

    divx = 1.0f / ray.direction_.x;
    if (divx >= 0.0f) {
        txmin = (min_.x - ray.origin_.x) * divx;
        txmax = (max_.x - ray.origin_.x) * divx;
    } else {
        txmin = (max_.x - ray.origin_.x) * divx;
        txmax = (min_.x - ray.origin_.x) * divx;
    }

    divy = 1.0f / ray.direction_.y;
    if (divy >= 0.0f) {
        tymin = (min_.y - ray.origin_.y) * divy;
        tymax = (max_.y - ray.origin_.y) * divy;
    } else {
        tymin = (max_.y - ray.origin_.y) * divy;
        tymax = (min_.y - ray.origin_.y) * divy;
    }

    if ((txmin > tymax) || (tymin > txmax))
        return false;

    if (tymin > txmin)
        txmin = tymin;

    if (tymax < txmax)
        txmax = tymax;

    divz = 1.0f / ray.direction_.z;
    if (divz >= 0.0f) {
        tzmin = (min_.z - ray.origin_.z) * divz;
        tzmax = (max_.z - ray.origin_.z) * divz;
    } else {
        tzmin = (max_.z - ray.origin_.z) * divz;
        tzmax = (min_.z - ray.origin_.z) * divz;
    }

    if ((txmin > tzmax) || (tzmin > txmax))
        return false;

    if (tzmin > txmin)
        txmin = tzmin;

    if (tzmax < txmax)
        txmax = tzmax;

    return true;
};

AABB AABB::operator+(AABB &other) const {
    return AABB(glm::min(min_, other.min_), glm::max(max_, other.max_));
}
