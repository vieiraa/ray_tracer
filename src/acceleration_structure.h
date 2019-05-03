#pragma once

#include "ray.h"
#include "intersection_record.h"

class AccelerationStructure {
public:
    virtual bool intersect(const Ray &ray,
                           IntersectionRecord &ir,
                           unsigned &intersection_tests,
                           unsigned &intersections) const = 0;
};
