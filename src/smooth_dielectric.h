#pragma once

#include "material.h"

class SmoothDielectric : public Material {
public:

    SmoothDielectric(glm::vec3 &r, glm::vec3 &e);
    glm::vec3 fr(const glm::vec3 &wi,
                 const glm::vec3 &wo);
    float p();
    glm::vec3 getDirection(const Ray &r, glm::vec3 &normal);
    glm::vec3 get_reflected_direction(const Ray &r,  glm::vec3 &normal);
    glm::vec3 get_refracted_direction(const Ray &r,  glm::vec3 &normal, float ni, float nt);
    float schlick(const Ray &r, glm::vec3 &normal, float ni, float nt);
};
