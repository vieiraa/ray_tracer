#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "primitive.h"
#include "sphere.h"
#include "triangle_naive.h"
#include "triangle_fast.h"
#include "triangle_mesh.h"
#include "acceleration_structure.h"

class Scene {
public:
    Scene();
    ~Scene();

    bool intersect(const Ray &ray,
                   IntersectionRecord &intersection_record) const;
    void load();

    std::vector<Primitive::PrimitiveUniquePtr> primitives_;
    std::unique_ptr<AccelerationStructure> acc_;
};
