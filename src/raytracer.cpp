#include "raytracer.h"
#include "material.h"

RayTracer::RayTracer(Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      Buffer &buffer) :
        camera_(camera),
        scene_(scene),
        background_color_(background_color),
        buffer_(buffer)
{}

void RayTracer::integrate() {
    IntersectionRecord intersection_record;

    for (unsigned y = 0; y < buffer_.height_; y++) {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * y / ( buffer_.height_ - 1 )
                        << "%";

        std::clog << progress_stream.str();

        for (unsigned x = 0; x < buffer_.width_; x++) {
            intersection_record.t_ = std::numeric_limits< double >::max();

            Ray ray( camera_.getWorldSpaceRay(glm::vec2(x, y)));
            auto aux = intersection_record.material_.lock();

            if (scene_.intersect(ray, intersection_record))
                buffer_.buffer_data_[x][y] = aux->reflected_;
        }
    }

    std::clog << std::endl;
}
