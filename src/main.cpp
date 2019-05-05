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
			  glm::vec3{ 0.0f, -0.75f, 1.0f },     // position
			  glm::vec3{ 0.0f, -1.0f,  0.0f },     // up
			  glm::vec3{ 0.0f, -0.75f, -3.0f } );   // look at

    Scene scene;


    scene.load();

    std::cout << "\n\n######################################################################";
    //construction tree time
    clock_t start1 = clock();
    scene.bvh_ = new BVH(scene.primitives_);
    clock_t duration1 = (float)(clock() - start1) * 1000.0 / CLOCKS_PER_SEC;
    std::cout << "\nBVH construction time: " << duration1 / 1000.0 << "s" << std::endl;

    Buffer rendering_buffer( x_resolution, y_resolution );
    glm::vec3 background_color( 1.0f, 1.0f, 1.0f );

    // Set up the renderer.
    PathTracer rt( camera,
                  scene,
                  background_color,
                  rendering_buffer );

#if __cplusplus < 201103L
    clock_t start2 = clock();
#else
    auto start = std::chrono::high_resolution_clock::now();
#endif



    rt.integrate(); // Renders the final image.

    //Primitives number
    std::cout << "\nNumero de primitivas: " << scene.primitives_.size();

    //height tree
    auto heigth = scene.bvh_->height(scene.bvh_->getRoot());
    std::cout << "\nProfundidade da arvore: " << heigth;

#if __cplusplus < 201103L
    clock_t duration2 = (float)(clock() - start2) * 1000.0 / CLOCKS_PER_SEC;
#else
    auto duration = std::chrono::
	duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
#endif

    std::cout << "\nElapsed time: " << duration2 / 1000.0 << "s" << std::endl;
    std::cout << "######################################################################\n\n";


    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "teste.ppm" );

    return 0;
}
