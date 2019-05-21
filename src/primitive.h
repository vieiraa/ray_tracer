#pragma once

#include <memory>
#include "aabb.h"
#include "ray.h"
#include "intersection_record.h"
#include "material.h"

class Primitive {
public:
    typedef std::unique_ptr<Primitive> PrimitiveUniquePtr;

    Primitive();
    explicit Primitive(const AABB &aabb);
    virtual ~Primitive();
    virtual bool intersect(const Ray &ray,
                           IntersectionRecord &intersection_record ) const = 0;
    AABB getAABB() const;

    std::shared_ptr<Material> material_;

protected:
    AABB aabb_;
};
