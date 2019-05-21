#include "path_tracer.h"
#include "raytracer.h"
#include "material.h"
#include "onb.h"
#include <glm/ext/scalar_constants.hpp>
#include <omp.h>
#include <iostream>
#include <thread>

const int NUM_SAMPLES = 10;

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
            glm::vec3 wi;

            glm::vec3 dir;
            float dot;
            dir = ir.material_.lock()->getDirection(r.direction_, ir.normal_, dot);

            ONB onb;
            onb.setFromV(ir.normal_);
            wi = glm::transpose(onb.getBasisMatrix()) * -r.direction_;

            Ray next_ray(ir.position_ + dir * 0.0001f, dir);

            auto aux = ir.material_.lock();

            Lo = aux->emitted_ + (aux->fr(wi) / aux->p()) * L(next_ray, ++curr_depth) * dot;
        }
    }

    return Lo;
}

void PathTracer::integrate(void) {
    int num_threads = std::thread::hardware_concurrency();
    omp_set_num_threads(num_threads);

#pragma omp parallel for schedule(dynamic, 1)
    for (unsigned y = 0; y < buffer_.height_; y++) {
        std::stringstream progress_stream;
        progress_stream << "\rProgress .........................: "
                        << std::fixed << std::setw(6)
                        << std::setprecision(2)
                        << 100.0f * y / (buffer_.height_ - 1)
                        << "%";
        std::clog << progress_stream.str();

        for (unsigned x = 0; x < buffer_.width_; x++) {
            for (int sample = 0; sample < NUM_SAMPLES; sample++) {

                Ray ray(camera_.getWorldSpaceRay(glm::vec2{ x, y }));
                buffer_.buffer_data_[x][y] += L(ray, 0);
            }

            buffer_.buffer_data_[x][y] /= NUM_SAMPLES;
        }
    }

    std::clog << "\n";
    std::cout << "\nNumber of threads: " << num_threads << "\n";
}
