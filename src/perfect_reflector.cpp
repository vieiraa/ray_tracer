#include "perfect_reflector.h"
#include <math.h>
#include <glm/glm.hpp>
#include "intersection_record.h"
#include "onb.h"

const float pi = 3.14159265358979323846;

PerfectReflector::PerfectReflector() :
    Material(glm::vec3(1,1,1), glm::vec3(0,0,0))
{}

PerfectReflector::PerfectReflector(const glm::vec3 &r) :
    Material(r, glm::vec3(0))
{}

PerfectReflector::~PerfectReflector() {}

glm::vec3 PerfectReflector::fr(const glm::vec3 &wi) {
    return reflected_ / wi.y;
}

glm::vec3 PerfectReflector::getDirection(const glm::vec3 &dir,
                                         const glm::vec3 &normal,
                                         float &dot)
{
    dot = glm::dot(dir, normal);
    glm::vec3 ret = 2.0f * normal * (glm::dot(dir, normal)) - dir;
    if (dot < 0.0f) {
        dot = -dot;
        ret = -ret;
    }

    return ret;
}

float PerfectReflector::p() {
    return 1.0f;
}
