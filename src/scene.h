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

class Scene
{
public:

    Scene( void );

    ~Scene( void );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    void load( void );

    std::vector< Primitive::PrimitiveUniquePtr > primitives_;

};

