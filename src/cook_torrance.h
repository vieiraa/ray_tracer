#pragma once

#include "material.h"

class CookTorrance : public Material {
    float m_;
public:
    CookTorrance(const glm::vec3 &r, const float m);

    glm::vec3 fr(const glm::vec3 &wi,
                 const glm::vec3 &wo,
                 const glm::vec3 &normal);
    float p();
    glm::vec3 getDirection(const Ray &r, glm::vec3 &normal);
};
