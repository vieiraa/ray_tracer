#pragma once

#include "camera.h"
#include "ray.h"

class OrthographicCamera : public Camera
{
public:

    OrthographicCamera( void );

    OrthographicCamera( const float min_x,
                        const float max_x,
                        const float min_y,
                        const float max_y,
                        const glm::ivec2 &resolution,
                        const glm::vec3 &position,
                        const glm::vec3 &up_vector,
                        const glm::vec3 &look_at );

    Ray getWorldSpaceRay( const glm::vec2 &pixel_coord );

    glm::vec3 ray_origin_;

    float min_x_;

    float max_x_;

    float min_y_;

    float max_y_;

};

