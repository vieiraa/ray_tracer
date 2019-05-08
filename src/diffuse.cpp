#include "diffuse.h"
#include "random.h"
#include "ray.h"
#include "onb.h"

const float pi = 3.14159265358979323846;

Diffuse::Diffuse(glm::vec3 r, glm::vec3 e) :
    Material(r, e)
{}

Diffuse::~Diffuse() {}

glm::vec3 Diffuse::fr(const glm::vec3 &wi) {
    return reflected_ / pi;
}

float Diffuse::p() {
    return 1/(2 * pi);
}

glm::vec3 Diffuse:: getDirection(const glm::vec3 &d,
                                 const glm::vec3 &normal,
                                 float &dot)
{
    glm::vec3 dir;

    do {
        dir = 2.0f * glm::vec3(random.get(), random.get(), random.get()) - glm::vec3(1, 1, 1);
    } while (glm::dot(dir, dir) >= 1);

    ONB onb;
    onb.setFromV(normal);
    dir = glm::normalize(dir * onb.getBasisMatrix());

    dot = glm::dot(dir, normal);
    if (dot < 0) {
        dir = -dir;
        dot = -dot;
    }

    return dir;
}
