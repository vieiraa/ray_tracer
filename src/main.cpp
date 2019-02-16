#include "main.h"

#if __cplusplus < 201103L
#include <ctime>
#else
#include <chrono>
#endif

int main( void )
{
    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;

    OrthographicCamera camera( -1.25f,
                                1.25f,
                               -1.25f,
                                1.25f,
                                glm::ivec2{ x_resolution, y_resolution },
                                glm::vec3{ 0.0f, 0.0f,  1.0f },     // position
                                glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } );   // look at
    Scene scene;

    scene.load();

    Buffer rendering_buffer( x_resolution, y_resolution );
    glm::vec3 background_color( 0.0f, 0.0f, 0.0f );

    // Set up the renderer.
    RayTracer rt( camera,
                  scene,
                  background_color,
                  rendering_buffer );

#if __cplusplus < 201103L
    clock_t start = clock();
#else
    auto start = std::chrono::high_resolution_clock::now();
#endif

    rt.integrate(); // Renders the final image.

#if __cplusplus < 201103L
    clock_t duration = (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;
#else
    auto duration = std::chrono::
	duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
#endif

    std::cout << "Elapsed time: " << duration / 1000.0 << "s" << std::endl;

    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "output_image.ppm" );

    return 0;
}

