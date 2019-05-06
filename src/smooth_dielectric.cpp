#include "smooth_dielectric.h"
#include "random.h"
#include "intersection_record.h"
#include <iostream>


const float pi = 3.14159265358979323846;

SmoothDielectric::SmoothDielectric(glm::vec3 &r, glm::vec3 &e): Material(r, e)
{
    material_ = 2;

}

float SmoothDielectric::schlick(const Ray &r, glm::vec3 &normal, float ni, float nt) {
    float R0 = (ni - nt) / (ni + nt);
    R0 *= R0;

    float cos1 = -glm::dot(normal, r.direction_);

    if (ni > nt) {
        float n = ni / nt;
        float cos2 = 1.0f - n * n * (1.0f - cos1 * cos1);

        if (cos2 < 0.0f)     // TIR
            return 1.0f;
    }

    float aux = 1-cos1;
    
    return R0 + (1.0f - R0) * aux * aux * aux * aux * aux;
}

glm::vec3 SmoothDielectric::fr(const glm::vec3 &wi, const glm::vec3 &wo) {

    return reflected_ / wi.y;
}

glm::vec3 SmoothDielectric::get_reflected_direction(const Ray &r, glm::vec3 &normal) {

    return 2.0f * normal * (glm::dot(r.direction_, normal)) - r.direction_;
}

glm::vec3 SmoothDielectric::get_refracted_direction(const Ray &r, glm::vec3 &normal, float ni, float nt) {
    //std::cout << "Refracao";
    float n = ni / nt;
    float cos_i = -glm::dot(r.direction_, normal);
    float cos_t = sqrt(1 - (n * n) * (1.0f - cos_i * cos_i));

    return n * (r.direction_ + cos_i * normal) - normal * cos_t;

}

glm::vec3 SmoothDielectric::getDirection(const Ray &r, glm::vec3 &normal) {
    float n_i_, n_t_;
    float cos = glm::dot(r.direction_,normal);
    float schlick_;
    glm::vec3 new_direction;
    
    
    if (cos < 0.0f) { //entering

        n_i_ = 1.0f;
        n_t_ = 1.5f;

        schlick_ = schlick(r, normal, n_i_, n_t_);
        
        if (random.get() < schlick_) {
            
            return new_direction = get_reflected_direction(r, normal);
        }
        else {
            
            return new_direction = get_refracted_direction(r, normal, n_i_, n_t_);
        }
    }
    else {         //getting out
        
        n_i_ = 1.5;
        n_t_ = 1.0;
        normal = -normal;

        schlick_ = schlick(r, normal, n_i_, n_t_);      
        
        if (random.get() < schlick_) {
            return new_direction = get_reflected_direction(r, normal);
        }
        else {
             //std::cout << "\naqui";
             return new_direction = get_refracted_direction(r, normal, n_i_, n_t_);
        }
    }    
}

float SmoothDielectric::p() {

    return 1;
}
