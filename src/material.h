#pragma once

#include <glm/glm.hpp>
#include "brdf.h"
#include "random.h"
#include "ray.h"
#include "intersection_record.h"

class Material {
public:
    Material() = default;
    Material(glm::vec3 r, glm::vec3 e);

    //BRDF *brdf;

    virtual glm::vec3 fr(const glm::vec3 &wi,
                         const glm::vec3 &wo) = 0;
    virtual float p() = 0;
    virtual glm::vec3 getDirection(const Ray &r, const glm::vec3 &normal) = 0;
    virtual glm::vec3 get_reflected_direction(const Ray &r, const glm::vec3 &normal) = 0;
    virtual glm::vec3 get_refracted_direction(const Ray &r, IntersectionRecord &intersection_record, float n1, float n2) = 0;
    virtual float schlick(const Ray &r, const glm::vec3 &normal, float ni, float nt) = 0;

    glm::vec3 reflected_;
    glm::vec3 emitted_;

protected:
    Random random;
};
