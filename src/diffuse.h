#pragma once

#include "material.h"
#include <glm/glm.hpp>
#include "ray.h"

class Diffuse : public Material
{
public:
    Diffuse(glm::vec3 r, glm::vec3 e);
    virtual ~Diffuse();

    glm::vec3 fr(const glm::vec3 &wi,
                 const glm::vec3 &wo,
                 const glm::vec3 &normal);
    float p();

    glm::vec3 getDirection(const Ray &r, glm::vec3 &normal);
    glm::vec3 get_reflected_direction(const Ray &r,  glm::vec3 &normal);

};
