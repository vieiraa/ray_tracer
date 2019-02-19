#include "pinhole_camera.h"

PinholeCamera::PinholeCamera( void )
{}

PinholeCamera::PinholeCamera( const float min_x,
                                        const float max_x,
                                        const float min_y,
                                        const float max_y,
                                        const glm::ivec2 &resolution,
                                        const glm::vec3 &position,
                                        const glm::vec3 &up_vector,
                                        const glm::vec3 &look_at ) :
        Camera::Camera{ resolution,
                        position,
                        up_vector,
                        look_at },


        position_{position},
        min_x_{ min_x },
        max_x_{ max_x },
        min_y_{ min_y },
        max_y_{ max_y }
{}


Ray PinholeCamera::getWorldSpaceRay( const glm::vec2 &pixel_coord ) const
{

    glm::vec3 ray_origin_ = position_;

    glm:: vec3 buffer_position = {0.0f,0.0f,-1.0f};

    glm::vec3 direction( pixel_coord[0] - ray_origin_[0],
                        pixel_coord[1] - ray_origin_[1],
                        buffer_position[2] - ray_origin_[2]);

    return Ray{ onb_.getBasisMatrix() * ray_origin_ + position_,
                glm::normalize( onb_.getBasisMatrix() * direction) };
}

