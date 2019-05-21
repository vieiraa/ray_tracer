#pragma once

#include "material.h"

class CookTorrance : public Material {
    float m_;

public:
    CookTorrance(const glm::vec3 &r, const float m);

    glm::vec3 fr(const glm::vec3 &wi);
    float p();
    glm::vec3 getDirection(const glm::vec3 &dir, const glm::vec3 &normal, float &dot);
};
