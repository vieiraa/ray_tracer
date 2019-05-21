#include "ray.h"

Ray::Ray() :
    origin_(glm::vec3(0.0f)),
    direction_(glm::vec3(0.0f, 0.0f, -1.0f))
{}

Ray::Ray(const glm::vec3 &origin,
         const glm::vec3 &direction) :
    origin_(origin),
    direction_(direction)
{}
