#include "path_tracer.h"

#include "raytracer.h"
#include "material.h"
#include "onb.h"
#include "random.h"
#include <glm/ext/scalar_constants.hpp>
#include <omp.h>


const float PI = glm::pi<float>();
const int NUM_SAMPLES = 40;

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
            glm::vec3 dir;

            do {
                dir = 2.0f * glm::vec3(random.get(), random.get(), random.get()) - glm::vec3(1, 1, 1);
            } while (glm::dot(dir, dir) >= 1);

            ONB onb;
            onb.setFromV(ir.normal_);
            dir = glm::normalize(dir * onb.getBasisMatrix());

            float dot = glm::dot(dir,ir.normal_);
            if (dot < 0) {
                dir = -dir;
                dot = -dot;
            }
            
            Ray refl_ray(ir.position_ + dir * 0.0001f, dir);
            
            auto aux = ir.material_.lock();

            Lo = aux->emitted_ + 2 * PI * aux->fr() * L(refl_ray, ++curr_depth) * dot;
        }
    }

    return Lo;
}

void PathTracer::integrate( void ){
	//int num_threads = omp_get_num_threads();

	for (auto y = 0; y < buffer_.h_resolution_; ++y) {

		#pragma omp parallel for schedule( dynamic, 1 )
        for (auto x = 0; x < buffer_.h_resolution_; ++x) {
			for (int sample = 0; sample < NUM_SAMPLES; sample++) {
				
				Ray ray( camera_.getWorldSpaceRay( glm::vec2{ x, y } ) );
				buffer_.buffer_data_[x][y] += L(ray, 0);
            }

			buffer_.buffer_data_[x][y] /= NUM_SAMPLES;
		}
    }
                  

    std::clog << std::endl;
}
