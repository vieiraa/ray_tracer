#include <chrono>
#include <glm/geometric.hpp>

#include "camera.h"
#include "orthographic_camera.h"
#include "pinhole_camera.h"
#include "scene.h"
#include "buffer.h"
#include "raytracer.h"
#include "path_tracer.h"
#include "bvh.h"

int main() {
    unsigned int width = 256;
    unsigned int height = 256;

    PinholeCamera camera(-2.5f,
                         2.5f,
                         -2.5f,
                         2.5f,
                         5.0f,
                         glm::ivec2(width, height),
                         glm::vec3(0.0f, 0.0f, 6.0f), // position
                         glm::vec3(0.0f, -1.0f,  0.0f), // up
                         glm::vec3(0.0f, 0.0f, -1.0f)); // look at

    Scene scene;
    scene.load();

    //Primitives number
    std::cout << "\nNumber of primitives: " << scene.primitives_.size();

    // acceleration structure construction time
    auto start1 = std::chrono::high_resolution_clock::now();
    scene.acc_ = std::make_unique<BVH_SAH>(scene.primitives_);
    auto duration1 = std::chrono::
	duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start1);
    std::cout << "\nBVH construction time: " << duration1.count() << "s" << std::endl;

    Buffer rendering_buffer(width, height);
    glm::vec3 background_color(1.0f, 1.0f, 1.0f);

    // Set up the renderer.
    PathTracer rt(camera,
                  scene,
                  background_color,
                  rendering_buffer);

    auto start2 = std::chrono::high_resolution_clock::now();

    rt.integrate(); // Renders the final image.

    auto duration2 = std::chrono::
	duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start2);

    std::cout << "\nElapsed time: " << duration2.count() << "s" << std::endl;

    // Save the rendered image to a .ppm file.
    rendering_buffer.save("teste.ppm");

    return 0;
}
