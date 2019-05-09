#include "main.h"

#if __cplusplus < 201103L
#include <ctime>
#else
#include <chrono>
#endif

#include <glm/geometric.hpp>

int main( void )
{
    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;

    PinholeCamera camera( -2.5f,
			  2.5f,
			  -2.5f,
			  2.5f,
			  5.0f,
			  glm::ivec2{ x_resolution, y_resolution },
			  glm::vec3{ 5.9f, 2.0f, 1.8f },     // position
			  glm::vec3{ 0.0f, -1.0f,  0.0f },     // up
			  glm::vec3{ 0.0f, 0.0f, -3.0f } );   // look at

    Scene scene;
    scene.load();

    //construction tree time
    auto start1 = std::chrono::high_resolution_clock::now();
    scene.bvh_ = new BVH(scene.primitives_);
    auto duration1 = std::chrono::
	duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start1).count();
    std::cout << "\nBVH construction time: " << duration1 / 1000.0 << "s" << std::endl;

    Buffer rendering_buffer( x_resolution, y_resolution );
    glm::vec3 background_color( 1.0f, 1.0f, 1.0f );

    // Set up the renderer.
    PathTracer rt( camera,
                  scene,
                  background_color,
                  rendering_buffer );

    auto start2 = std::chrono::high_resolution_clock::now();

    rt.integrate(); // Renders the final image.

    //Primitives number
    std::cout << "\nNumero de primitivas: " << scene.primitives_.size();

    //height tree
    auto heigth = scene.bvh_->height(scene.bvh_->getRoot());
    std::cout << "\nProfundidade da arvore: " << heigth;

    auto duration2 = std::chrono::
	duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start2).count();

    std::cout << "\nElapsed time: " << duration2 / 1000.0 << "s" << std::endl;

    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "teste.ppm" );

    return 0;
}
