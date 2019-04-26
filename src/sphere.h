#pragma once

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Sphere : public Primitive
{
public:

    Sphere( void );

    Sphere( const glm::vec3 &center,
            float radius );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    void computeBounds(const glm::vec3 &plane_normal, float &near, float &far) const;

    glm::vec3 center_ = { 0.0f, 0.0f, 0.0f };

    float radius_= 1.0f;

private:

    static const float kIntersectionTestEpsilon_;
};
