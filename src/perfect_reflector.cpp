#include "perfect_reflector.h"
#include <math.h>
#include <glm/glm.hpp>
#include "intersection_record.h"
#include "onb.h"

const float pi = 3.14159265358979323846;

PerfectReflector::PerfectReflector() : Material(glm::vec3(0), glm::vec3(0)) {

    //ctor

}

PerfectReflector::~PerfectReflector() {

    //dtor
}

glm::vec3 PerfectReflector::fr(const glm::vec3 &wi,
                               const glm::vec3 &wo)
{
    return glm::vec3(1, 1, 1);
}

glm::vec3 PerfectReflector::getDirection(const Ray &r, const glm::vec3 &normal) {
    // ONB onb;
    // onb.setFromV(normal);
    // glm::vec3 dir = glm::transpose(onb.getBasisMatrix()) * r.direction_;
    // dir = glm::vec3(-dir.x, dir.y, -dir.z);


    //return dir;
    return 2.0f * normal * (glm::dot(r.direction_, normal)) - r.direction_;
}

float PerfectReflector::p() {
    return 1;
}
