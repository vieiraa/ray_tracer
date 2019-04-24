#include "perfect_reflector.h"
#include <math.h>
#include <glm/glm.hpp>
#include "intersection_record.h"

const float pi = 3.14159265358979323846;

Perfect_reflector::Perfect_reflector(glm::vec3 r, glm::vec3 e) : Material(r, e) {

    //ctor

} 

Perfect_reflector::~Perfect_reflector() {

    //dtor
}

int Perfect_reflector::diracDelta(float in, float out) {

    if (in - out == 0) {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

glm::vec3 Perfect_reflector::fr() {
    //glm::vec3 dir;
    //float theta = glm::acos(sqrt(pow((dir.x),2)+pow((dir.y),2))/dir.z);
   // float phi = glm::acos(dir.y/dir.x);


    //return diracDelta(cos(theta),cos(theta))*diracDelta(phi, phi + pi)/cos(theta);
}

glm::vec3 Perfect_reflector::getDirection(Ray r) {
    glm::vec3 dir;
    dir = { -r.direction_.x, r.direction_.y, -r.direction_.z };

    return dir;
}