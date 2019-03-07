#pragma once

#include <glm/glm.hpp>

class Ray
{
public:

    Ray( void );

    Ray( const glm::vec3 &origin,
         const glm::vec3 &direction );

    glm::vec3 origin_{ 0.0f, 0.0f, 0.0f };

    glm::vec3 direction_{ 0.0f, 0.0f, -1.0f };
};

