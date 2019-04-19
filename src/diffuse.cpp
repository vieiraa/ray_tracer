#include "diffuse.h"
#include "random.h"

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

glm::vec3 Diffuse::getDirection() {
	Random random;
	glm::vec3 dir;

	do {
		dir = 2.0f * glm::vec3(random.get(), random.get(), random.get()) - glm::vec3(1, 1, 1);
	} while (glm::dot(dir, dir) >= 1);

	return dir;

}
