#include "path_tracer.h"

#include "raytracer.h"
#include "material.h"
#include "onb.h"
#include "random.h"
#include <math.h>

const float pi = 3.14159265358979323846;

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
    glm::vec3 Lo;
    IntersectionRecord ir;

    if (curr_depth < 5) {
        if (scene_.intersect(r, ir)) {
            float r1 = random.get();
            float r2 = random.get();
            
            while (r1 == 1.0f)
                r1 = random.get();
            while (r2 == 1.0f)
                r2 = random.get();

            auto theta = glm::acos(1 - r1);
            auto phi = 2 * pi * r2;
            auto radius = 1;

            float x = radius * glm::sin(theta) * glm::cos(phi);
            float y = radius * glm::sin(theta) * glm::sin(phi);
            float z = radius * glm::cos(theta);

            glm::vec3 dir(x, y, z);
            ONB onb;
            onb.setFromV(ir.normal_);
            dir = glm::normalize(dir * onb.getBasisMatrix());

            Ray refl_ray(ir.position_, dir);
            float dot = glm::dot(ir.normal_, refl_ray.direction_);

            if (dot < 0) {
                refl_ray.direction_ *= -1;
                dot = -dot;
            }

            Lo = ir.material_->emitted_ + ir.material_->fr() * L(refl_ray, curr_depth++) * glm::dot(ir.normal_, refl_ray.direction_);
        }
    }

    return Lo;
}

void PathTracer::integrate( void )
{
    IntersectionRecord intersection_record;

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
            for (int sample = 0; sample < 5; sample++) {
                intersection_record.t_ = std::numeric_limits< double >::max();

                Ray ray = ( camera_.getWorldSpaceRay( glm::vec2{ x, y } ) );

                buffer_.buffer_data_[x][y] += L(ray, 0);

            }

            buffer_.buffer_data_[x][y] /= 5;

        }
    }

    std::clog << std::endl;
}

