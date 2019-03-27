#include "path_tracer.h"

#include "raytracer.h"
#include "material.h"
#include "onb.h"
#include "random.h"
#include <math.h>
#include <assert.h>
#include <glm/ext/scalar_constants.hpp>
#include <thread>

const float PI = glm::pi<float>();
const int NUM_SAMPLES = 4000;

PathTracer::PathTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      Buffer &buffer ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer )
{}

glm::vec3 PathTracer::L(const Ray &r, int curr_depth) {
    glm::vec3 Lo(0, 0, 0);
    IntersectionRecord ir;
    ir.t_ = std::numeric_limits<float>::max();

    if (curr_depth < 5) {
        if (scene_.intersect(r, ir)) {
            float r1 = random.get();
            float r2 = random.get();

            while (r1 == 1.0f)
                r1 = random.get();
            while (r2 == 1.0f)
                r2 = random.get();

            float theta = glm::acos(1 - r1);
            float phi = 2.0f * PI * r2;
            float radius = 1.0f;

            float x = radius * glm::sin(theta) * glm::cos(phi);
            float y = radius * glm::sin(theta) * glm::sin(phi);
            float z = radius * glm::cos(theta);

            glm::vec3 dir(x, y, z);
            ONB onb;
            onb.setFromV(ir.normal_);
            dir = glm::normalize(dir * onb.getBasisMatrix());

            Ray refl_ray(ir.position_ + dir * 0.0001f, dir);
            float dot = glm::dot(refl_ray.direction_,ir.normal_);

            if (dot < 0) {
                refl_ray.direction_ = - refl_ray.direction_;
                dot = -dot;
            }

            Lo = ir.material_->emitted_ + 2 * PI * ir.material_->fr() * L(refl_ray, ++curr_depth) * dot;
        }
    }

    return Lo;
}

void PathTracer::integrate( void )
{
    int num_threads = std::thread::hardware_concurrency();
    num_threads = num_threads ? num_threads : 4;
    std::vector<std::thread> threads(num_threads);
    int jump = buffer_.h_resolution_ / num_threads;
    auto worker = [&](int begin, int end) {
                      for (auto y = begin; y < end; ++y) {
                          for (auto x = 0; x < buffer_.h_resolution_; ++x) {
                              for (int sample = 0; sample < NUM_SAMPLES; sample++) {
                                  Ray ray( camera_.getWorldSpaceRay( glm::vec2{ x, y } ) );

                                  buffer_.buffer_data_[x][y] += L(ray, 0);
                              }

                              buffer_.buffer_data_[x][y] /= NUM_SAMPLES;
                          }
                      }
                  };
    
    auto begin = 0;
    for (auto &t : threads) {
        t = std::thread(worker, begin + 0, begin + jump);
        begin += jump;
    }

    for (auto &&t : threads) {
        t.join();
    }

    std::clog << std::endl;
}

