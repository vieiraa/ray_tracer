#include "perfect_reflector.h"
#include <math.h>
#include <glm/glm.hpp>
#include "intersection_record.h"
#include "onb.h"

const float pi = 3.14159265358979323846;

PerfectReflector::PerfectReflector() : Material(glm::vec3(1,1,1), glm::vec3(0,0,0)) {

    //reflected_ = { 1.0f, 1.0f, 1.0f };

}

PerfectReflector::PerfectReflector(const glm::vec3 &r) : Material(r, glm::vec3(0)) {

    //ctor

}

PerfectReflector::~PerfectReflector() {

    //dtor
}

glm::vec3 PerfectReflector::fr(const glm::vec3 &wi,
                               const glm::vec3 &wo)
{
    return reflected_ / wi.y;
}

glm::vec3 PerfectReflector::get_reflected_direction(const Ray &r,  glm::vec3 &normal) {
    // ONB onb;
    // onb.setFromV(normal);
    // glm::vec3 dir = glm::transpose(onb.getBasisMatrix()) * r.direction_;
    // dir = glm::vec3(-dir.x, dir.y, -dir.z);


    //return dir;
    return 2.0f * normal * (glm::dot(r.direction_, normal)) - r.direction_;
}

glm::vec3 PerfectReflector::getDirection(const Ray &r, glm::vec3 &normal) {

    return get_reflected_direction(r, normal);
}



float PerfectReflector::p() {
    return 1;
}
