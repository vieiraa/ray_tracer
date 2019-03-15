#include "diffuse.h"

const float pi = 3.14159265358979323846;

Diffuse::Diffuse(glm::vec3 r, glm::vec3 e) : Material(r, e)
{
    //ctor
}

Diffuse::~Diffuse()
{
    //dtor
}

glm::vec3 Diffuse::fr() {
    return reflected_ / pi;
}
