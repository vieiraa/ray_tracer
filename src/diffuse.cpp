#include "diffuse.h"
#include "random.h"
#include "ray.h"
#include "onb.h"

const float pi = 3.14159265358979323846;

Diffuse::Diffuse(glm::vec3 r, glm::vec3 e) : Material(r, e)
{
    //ctor
    material_ = 0;
}

Diffuse::~Diffuse()
{
    //dtor
}

glm::vec3 Diffuse::fr(const glm::vec3 &wi,
                      const glm::vec3 &wo,
                      const glm::vec3 &normal) {
    return reflected_ / pi;
}

float Diffuse::p() {
    return 1/(2 * pi);
}

glm::vec3 Diffuse::get_reflected_direction(const Ray &r,  glm::vec3 &normal) {
    glm::vec3 dir;

    do {
        dir = 2.0f * glm::vec3(random.get(), random.get(), random.get()) - glm::vec3(1, 1, 1);
    } while (glm::dot(dir, dir) >= 1);

    ONB onb;
    onb.setFromV(normal);
    dir = glm::normalize(dir * onb.getBasisMatrix());

    float dot = glm::dot(dir, normal);
    if (dot < 0) {
        dir = -dir;
        dot = -dot;
    }

    return dir;
}



glm::vec3 Diffuse:: getDirection(const Ray &r, glm::vec3 &normal) {

    return get_reflected_direction(r,normal);
}
