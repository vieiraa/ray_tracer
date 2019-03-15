#pragma once

#include <sstream>
#include <iomanip>
#include <cmath>

#include "camera.h"
#include "scene.h"
#include "buffer.h"
#include "random.h"

class PathTracer
{
public:

    PathTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer );

    void integrate( void );
    glm::vec3 L(Ray &r, int curr_depth);

private:
    Random random;

    Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

};
