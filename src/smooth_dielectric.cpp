#include "smooth_dielectric.h"
#include "random.h"
#include "intersection_record.h"
#include <iostream>

float schlick(const glm::vec3 &r_dir, const glm::vec3 &normal, float ni, float nt) {
    float R0 = (ni - nt) / (ni + nt);
    R0 *= R0;

    float cos1 = -glm::dot(normal, r_dir);

    if (ni > nt) {
        float n = ni / nt;
        float cos2 = 1.0f - n * n * (1.0f - cos1 * cos1);

        if (cos2 < 0.0f)     // TIR
            return 1.0f;
    }

    float aux = 1 - cos1;

    return R0 + (1.0f - R0) * aux * aux * aux * aux * aux;
}

SmoothDielectric::SmoothDielectric(const glm::vec3 &r, const glm::vec3 &e) :
    Material(r, e)
{}

inline glm::vec3 SmoothDielectric::fr(const glm::vec3 &wi) {
    return reflected_ / wi.y;
}

glm::vec3 getReflected(const glm::vec3 &dir, const glm::vec3 &normal) {
    return glm::normalize(2.0f * normal * (glm::dot(dir, normal)) - dir);
}

glm::vec3 getRefracted(const glm::vec3 &dir, const glm::vec3 &normal, float ni, float nt) {
    float n = ni / nt;
    float cos_i = -glm::dot(dir, normal);
    float cos_t = sqrt(1 - (n * n) * (1.0f - cos_i * cos_i));

    return glm::normalize(n * (dir + cos_i * normal) - normal * cos_t);
}

glm::vec3 SmoothDielectric::getDirection(const glm::vec3 &dir, const glm::vec3 &normal, float &cos) {
    float n_i_, n_t_;
    cos = glm::dot(dir, normal);
    float schlick_;

    if (cos < 0.0f) { // entering
        n_i_ = 1.0f;
        n_t_ = 1.5f;

        schlick_ = schlick(dir, normal, n_i_, n_t_);

        if (random.get() < schlick_)
            return getReflected(dir, normal);

        else
            return getRefracted(dir, normal, n_i_, n_t_);
    }

    else { // leaving
        n_i_ = 1.5;
        n_t_ = 1.0;
        glm::vec3 aux_normal = -normal;

        schlick_ = schlick(dir, aux_normal, n_i_, n_t_);

        if (random.get() < schlick_)
            return getReflected(dir, aux_normal);

        else
            return getRefracted(dir, aux_normal, n_i_, n_t_);
    }
}

inline float SmoothDielectric::p() {
    return 1.0f;
}
