#include <glm/gtc/constants.hpp>
#include "cook_torrance.h"

const float PI = glm::pi<float>();

inline glm::vec3 schlick(const glm::vec3 &R0, const float hwi) {
    float x = 1.0f - hwi;

    return R0 + (1.0f - R0) * x * x * x * x * x;
}

inline float beckmann(float nh, float m) {
    float nh2 = nh * nh;
    float m2 = m * m;
    float d1 = 1.0f / (PI * m2 * nh2 * nh2);
    float d2 = (nh2 - 1.0f) / (m2 * nh2);

    return d1 * glm::exp(d2);
}

CookTorrance::CookTorrance(const glm::vec3 &r, const float m)
    : Material(r, glm::vec3(0,0,0)), m_(m)
{}

glm::vec3 CookTorrance::fr(const glm::vec3 &wi) {
    float r1 = random.get();
    float r2 = random.get();

    float phi = 2.0f * PI * r2;
    float theta = glm::atan(glm::sqrt(-(m_ * m_) * glm::log(1 - r1)));
    glm::vec3 p(glm::cos(phi) * glm::sin(theta),
                glm::cos(theta),
                glm::sin(phi) * glm::sin(theta));

    glm::vec3 aux_wo = 2.0f * p * glm::dot(p, wi) - wi;

    glm::vec3 h = glm::normalize((wi + aux_wo) / 2.0f);
    float nh = glm::abs(h.y);
    float nwo = glm::abs(aux_wo.y);
    float nwi = glm::abs(wi.y);
    float hwo = glm::abs(glm::dot(h, aux_wo));
    float hwi = glm::abs(glm::dot(h, wi));

    // beckmann
    float D = beckmann(nh, m_);

    // geometric
    float g1 = 2 * nh / hwo;
    float G = glm::min(1.0f, glm::min(g1 * nwo, g1 * nwi));

    // fresnel (schlick)
    glm::vec3 F = schlick(reflected_, hwi);

    // cook-torrance
    glm::vec3 ct = (F * D * G) / (4.0f * nwo * nwi);

    float om = glm::dot(aux_wo, h);
    float pdf = D * (nh / (4.0f * om));

    return ct / pdf;
}

float CookTorrance::p() {
    return 1.0f;
}

glm::vec3 CookTorrance::getDirection(const glm::vec3 &dir, const glm::vec3 &normal, float &dot) {
    dot = glm::dot(dir, normal);
    glm::vec3 ret = glm::normalize(2.0f * normal * (glm::dot(dir, normal)) - dir);

    if (dot < 0.0f) {
        dot = -dot;
        ret = -ret;
    }

    return ret;
}
