#include "smooth_dielectric.h"

SmoothDielectric::SmoothDielectric(glm::vec3 &r, glm::vec3 &e)
    : Material(r, e)
{

}

glm::vec3 SmoothDielectric::fr(const glm::vec3 &wi, const glm::vec3 &wo) {
    //return reflected_ / pi;
}

glm::vec3 SmoothDielectric::getDirection(const Ray &r) {

}

float SmoothDielectric::p() {

}
