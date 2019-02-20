#include "pinhole_camera.h"

PinholeCamera::PinholeCamera( void )
{}

PinholeCamera::PinholeCamera( const float min_x,
			      const float max_x,
			      const float min_y,
			      const float max_y,
			      const float focal_distance,
			      const glm::ivec2 &resolution,
			      const glm::vec3 &position,
			      const glm::vec3 &up_vector,
			      const glm::vec3 &look_at ) :
        Camera::Camera{ resolution,
                        position,
                        up_vector,
                        look_at },


        position_{position},
	focal_distance_{focal_distance},
        min_x_{ min_x },
        max_x_{ max_x },
        min_y_{ min_y },
        max_y_{ max_y }
{}


Ray PinholeCamera::getWorldSpaceRay( const glm::vec2 &pixel_coord ) const
{
    glm::vec3 a(max_x_ - min_x_, 0, 0);
    glm::vec3 b(0, max_y_ - min_y_, 0);
    glm::vec3 c(min_x_, min_y_, -focal_distance_);
    float u = (pixel_coord.x + 0.5) / resolution_.x;
    float v = (pixel_coord.y + 0.5) / resolution_.y;
    glm::vec3 s = c + u * a + v * b;
    glm::vec3 direction = s;// - position_;

    return Ray{ position_,
                glm::normalize( onb_.getBasisMatrix() * direction) };
}

