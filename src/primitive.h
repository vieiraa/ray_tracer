#pragma once

#include <memory>
#include "aabb.h"
#include "ray.h"
#include "intersection_record.h"
#include "material.h"

class Primitive
{
public:
#if __cplusplus < 201103L
    typedef Primitive* PrimitiveUniquePtr;
#else
    typedef std::unique_ptr<Primitive> PrimitiveUniquePtr;
#endif

    Primitive();

    virtual ~Primitive();

    virtual bool intersect(const Ray &ray,
                           IntersectionRecord &intersection_record ) const = 0;
    virtual AABB getAABB(void) const = 0;

    std::shared_ptr<Material> material_;
};

