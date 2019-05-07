#include <glm/gtc/constants.hpp>
#include "cook_torrance.h"
//#include "schlick.h"
#include <iostream>

extern float schlick(const glm::vec3 &r_dir, const glm::vec3 &normal, float ni, float nt);

float beckmann(float nh, float m, float pdf) {

}

CookTorrance::CookTorrance(const glm::vec3 &r, const float m)
    : Material(r, glm::vec3(0,0,0)), m_(m)
{
    material_ = 3;
}

glm::vec3 CookTorrance::fr(const glm::vec3 &wi,
                           const glm::vec3 &wo,
                           const glm::vec3 &normal)
{
    auto PI = glm::pi<float>();

    if (wo.y < 0.0f)
        return glm::vec3(0.0f);

    float r1 = random.get();
    float r2 = random.get();
    float phi = 2.0f * PI * r2;
    float theta = glm::atan(glm::sqrt(-(m_ * m_) * glm::log(1.0f - r1)));

    glm::vec3 m(glm::cos(phi) * glm::sin(theta),
                glm::cos(theta),
                glm::sin(phi) * glm::sin(theta));

    auto aux = 2.0f * m * glm::dot(wi, m) - wi;

    glm::vec3 h = glm::normalize((aux + wi));// / 2.0f);
    // float nh = glm::abs(glm::dot(normal, h));
    // float nwo = glm::abs(glm::dot(normal, wo));
    // float nwi = glm::abs(glm::dot(normal, wi));
    // float hwo = glm::abs(glm::dot(h, wo));
    float nh = glm::abs(h.y);
    float nwi = glm::abs(wi.y);
    float nwo = glm::abs(aux.y);

    if (!nwi || !nwo)
        return glm::vec3(0.0f);

    float hwi = glm::abs(glm::dot(wi, h));
    float hwo = glm::abs(glm::dot(aux, h));
    //float hwi = glm::abs(glm::dot(h, wi));

    float nh2 = nh * nh;

    float m2 = m_ * m_;
    float d1 = 1 / (glm::pi<float>() * m2 * nh2 * nh2);

    float d2 = (nh2 - 1) / (m2 * nh2);

    float D =  d1 * glm::exp(d2);

    //float D = beckmann(nh, m_, pdf);
    float g1 = (2 * nh) / hwi;
    float G = glm::min(1.0f, glm::min(g1 * nwo, g1 * nwi));
    //float F = schlick(glm::abs(h), glm::abs(aux), 1.0f, 1.5f);
    float x = 1.0f - hwo;
    glm::vec3 F = reflected_ + (1.0f - reflected_) * x * x * x * x * x;
    //std::cout << "D = " << D << ", F = " << F << ", G = " << G << "\n";
    glm::vec3 ct = (F * D * G) / (4 * nwo * nwi);
    float pdf = glm::abs(glm::dot(aux, h));
    pdf = (d1 * glm::exp(d2) * nh) / (4 * pdf);


    return 1.0f / pdf * ct;
}

float CookTorrance::p() {
    return 1.0f;
}

glm::vec3 CookTorrance::getDirection(const Ray &r, glm::vec3 &normal) {
    return 2.0f * normal * (glm::dot(r.direction_, normal)) - r.direction_;
}
