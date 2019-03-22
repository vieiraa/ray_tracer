#include "path_tracer.h"

#include "raytracer.h"
#include "material.h"
#include "onb.h"
#include "random.h"
#include <math.h>
#include <assert.h>
#include <glm/ext/scalar_constants.hpp>

const float PI = glm::pi<float>();
const int NUM_SAMPLES = 100;

PathTracer::PathTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      Buffer &buffer ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer )
{}


std::ostream& operator<<(std::ostream& os, glm::mat3x3 m) {
    for (int i = 0; i < 3; i++) {
        os << m[i].x << " " << m[i].y << " " << m[i].z << "\n";
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, glm::vec3 v) {
    os << v.x << " " << v.y << " " << v.z << "\n";

    return os;
}

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

            Ray refl_ray(ir.position_, dir);
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
    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    // Loops over image rows
    for ( std::size_t y = 0; y < buffer_.v_resolution_; y++ )
    {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * y / ( buffer_.v_resolution_ - 1 )
                        << "%";

        std::clog << progress_stream.str();

        // Loops over image columns
        for ( std::size_t x = 0; x < buffer_.h_resolution_; x++ )
        {
            for (int sample = 0; sample < NUM_SAMPLES; sample++) {
                Ray ray( camera_.getWorldSpaceRay( glm::vec2{ x, y } ) );

                buffer_.buffer_data_[x][y] += L(ray, 0);
            }

            buffer_.buffer_data_[x][y] /= NUM_SAMPLES;
        }
    }

    std::clog << std::endl;
}

