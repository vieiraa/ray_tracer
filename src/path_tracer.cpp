#include "path_tracer.h"
#include "raytracer.h"
#include "material.h"
#include "onb.h"
#include <glm/ext/scalar_constants.hpp>
#include <omp.h>
#include <iostream>
#include <thread>

const float PI = glm::pi<float>();
const int NUM_SAMPLES = 400;

float schlick(const Ray &r, const glm::vec3 &normal, float ni, float nt) {
    float R0 = (ni - nt)/(ni + nt);
    R0 *= R0;

    float cos = glm::dot(r.direction_, normal);
    cos = 1 - cos;
    return R0 + (1 - R0) * cos * cos * cos * cos * cos;
}

PathTracer::PathTracer(Camera &camera,
                       const Scene &scene,
                       const glm::vec3 background_color,
                       Buffer &buffer ) :
    camera_(camera),
    scene_(scene),
    background_color_(background_color),
    buffer_(buffer)
{}

glm::vec3 PathTracer::L(const Ray &r, int curr_depth) {
    glm::vec3 Lo(0, 0, 0);
    IntersectionRecord ir;
    ir.t_ = std::numeric_limits<float>::max();

    if (curr_depth < 5) {
        if (scene_.intersect(r, ir)) {
            glm::vec3 wi, wo;

            glm::vec3 dir;
            dir = ir.material_.lock()->getDirection(r, ir.normal_);

            ONB onb;
            onb.setFromV(ir.normal_);
            wi = glm::transpose(onb.getBasisMatrix()) * -r.direction_;

            float dot = glm::dot(dir,ir.normal_);
            if (dot < 0) {
                dir = -dir;
                dot = -dot;
            }

            Ray refl_ray(ir.position_ + dir * 0.0001f, dir);

            auto aux = ir.material_.lock();

            Lo = aux->emitted_ + (aux->fr(wi, wo) / aux->p()) * L(refl_ray, ++curr_depth) * dot;
        }
    }

    return Lo;
}

void PathTracer::integrate(void) {

    int num_threads = std::thread::hardware_concurrency();
    omp_set_num_threads(num_threads);

    #pragma omp parallel for schedule(dynamic, 1)
    for (int y = 0; y < buffer_.h_resolution_; y++) {
        std::stringstream progress_stream;
        progress_stream << "\rProgress .........................: "
            << std::fixed << std::setw(6)
            << std::setprecision(2)
            << 100.0f * y / (buffer_.v_resolution_ - 1)
            << "%";
        std::clog << progress_stream.str();

        for (unsigned x = 0; x < buffer_.h_resolution_; x++) {
            for (int sample = 0; sample < NUM_SAMPLES; sample++) {

                Ray ray(camera_.getWorldSpaceRay(glm::vec2{ x, y }));
                buffer_.buffer_data_[x][y] += L(ray, 0);
            }

            buffer_.buffer_data_[x][y] /= NUM_SAMPLES;
        }
        num_threads = omp_get_num_threads();
    }
    std::cout << "\nO num de threads usados eh: " << num_threads;
    std::clog << std::endl;
}

void PathTracer::threads_color(void) {
    int num_threads;

    omp_set_num_threads(8);
#pragma omp parallel for schedule( dynamic, 1 )
    for (auto y = 0; y < buffer_.h_resolution_; ++y) {
        for (auto x = 0; x < buffer_.h_resolution_; ++x) {

            switch (int thread_num = omp_get_thread_num())
            {
            case(0):
                buffer_.buffer_data_[x][y] = glm::vec3(1.0f, 0.0f, 0.0f);
                break;
            case(1):
                buffer_.buffer_data_[x][y] = glm::vec3(1.0f, 0.5f, 0.0f);
                break;
            case(2):
                buffer_.buffer_data_[x][y] = glm::vec3(1.0f, 1.0f, 0.0f);
                break;
            case(3):
                buffer_.buffer_data_[x][y] = glm::vec3(0.0f, 1.0f, 0.0f);
                break;
            case(4):
                buffer_.buffer_data_[x][y] = glm::vec3(0.0f, 1.0f, 0.5f);
                break;
            case(5):
                buffer_.buffer_data_[x][y] = glm::vec3(0.0f, 1.0f, 1.0f);
                break;
            case(6):
                buffer_.buffer_data_[x][y] = glm::vec3(0.0f, 0.0f, 1.0f);
                break;
            case(7):
                buffer_.buffer_data_[x][y] = glm::vec3(1.0f, 1.0f, 1.0f);
                break;
            default:
                buffer_.buffer_data_[x][y] = glm::vec3(0.0f, 0.0f, 0.0f);
                break;
            }
            num_threads = omp_get_num_threads();
        }
    }
    std::cout << "o num de threads usados eh: " << num_threads;

    std::clog << std::endl;
}

void PathTracer::normal_color(void) {
    IntersectionRecord intersection_record;

    for (std::size_t y = 0; y < buffer_.v_resolution_; y++){
        for (std::size_t x = 0; x < buffer_.h_resolution_; x++){

            intersection_record.t_ = std::numeric_limits< double >::max();
            Ray ray(camera_.getWorldSpaceRay(glm::vec2{ x, y }));
            if (scene_.intersect(ray, intersection_record))

                buffer_.buffer_data_[x][y] = (glm::vec3(1.0f,0.0f,0.0f) + 1.0f)/2.0f * abs(intersection_record.normal_);
            //std::cout <<  "normal:"  << intersection_record.normal_.x <<","<<intersection_record.normal_.y<<","<<intersection_record.normal_.z;
        }
    }

    std::clog << std::endl;
}
