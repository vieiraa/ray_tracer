#pragma once

#include <iostream>
#include <iomanip>

#include <glm/glm.hpp>
#include "onb.h"
#include "ray.h"

class Camera {
public:
    Camera();
    Camera(const glm::ivec2 &resolution,
           const glm::vec3 &position,
           const glm::vec3 &up,
           const glm::vec3 &look_at);
    virtual ~Camera();

    void setPosition(const glm::vec3 &position);
    void setUp(const glm::vec3 &up);
    void setLookAt(const glm::vec3 &look_at);
    virtual Ray getWorldSpaceRay(const glm::vec2 &pixel_coord) = 0;

    glm::ivec2 resolution_;
    glm::vec3 up_{ 0.0f, 1.0f, 0.0f };
    glm::vec3 look_at_{ 0.0f, 0.0f, -1.0f };
    glm::vec3 position_{ 0.0f, 0.0f, 0.0f };
    glm::vec3 direction_{ 0.0f, 0.0f, -1.0f };
    ONB onb_;
};
