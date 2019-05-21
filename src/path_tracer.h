#pragma once

#include <sstream>
#include <iomanip>
#include <cmath>

#include "camera.h"
#include "scene.h"
#include "buffer.h"
#include "random.h"

class PathTracer {
    Camera &camera_;
    const Scene &scene_;
    glm::dvec3 background_color_;
    Buffer &buffer_;
    Random random;

public:
    PathTracer(Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer);

    void integrate();
    glm::vec3 L(const Ray &r, int curr_depth);
};
