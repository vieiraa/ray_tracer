#include "sphere.h"
#include "aabb.h"

Sphere::Sphere() {
    aabb_ = AABB(center_ - radius_,
                 center_ + radius_,
                 center_);
}

Sphere::Sphere(const glm::vec3 &center,
                float radius) :
    center_(center),
    radius_(radius)
{}

bool Sphere::intersect(const Ray &ray,
                        IntersectionRecord &ir) const
{
    /* Ray-sphere intersection test adapted from the very efficient algorithm presented in the article:
     *
     *     "Intersection of a Ray with a Sphere".
     *     Jeff Hultquist.
     *     Graphics Gems.
     *     Academic Press.
     *     1990.
     */

    float t1;
    float t2;

    glm::vec3 eo = center_ - ray.origin_;
    float v = glm::dot( eo, ray.direction_ );
    float disc = ( radius_ * radius_ ) - ( glm::dot( eo, eo ) - ( v * v ) );

    if ( disc < 0.0f )
        return false;                           // no intersection
    else
    {
        float d = sqrt( disc );
        t1 = v - d;                             // first intersection point
        t2 = v + d;                             // second intersection point
    }

    // Set the intersection record
    ir.t_ =  ( t1 > 0.00001f ) ? t1 : t2;
    ir.position_ = ray.origin_ + ir.t_ * ray.direction_;
    ir.normal_ = glm::normalize( ir.position_ - center_ );
    ir.material_ = material_;

    return true;
}
