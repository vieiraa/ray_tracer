#include "primitive.h"

Primitive::Primitive() {}

Primitive::Primitive(const AABB &aabb) : aabb_(aabb) {}

Primitive::~Primitive() {}

AABB& Primitive::getAABB() {
    return aabb_;
}
