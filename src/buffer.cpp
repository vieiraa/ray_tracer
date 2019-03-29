#include "buffer.h"
#include <glm/gtc/color_space.hpp>

// Creates a image buffer with default size (512 x 512 pixels)
Buffer::Buffer( void )
{
    // Allocate memory space for the image buffer
    buffer_data_.resize( h_resolution_, std::vector< glm::vec3 >( v_resolution_ ) );

    // Fills the image buffer with zeroes (black)
    for ( std::size_t y = 0; y < v_resolution_; y++ )
        for ( std::size_t x = 0; x < h_resolution_; x++ )
            buffer_data_[x][y] = glm::vec3{ 0.0f, 0.0f, 0.0f };
}

 // Creates a image buffer with a custom size (h_resolution x v_resolution pixels)
Buffer::Buffer( unsigned int h_resolution,
                unsigned int v_resolution ) :
        h_resolution_{ h_resolution },
        v_resolution_{ v_resolution }
{
    // Allocate memory space for the image buffer
    buffer_data_.resize( h_resolution_, std::vector< glm::vec3 >( v_resolution_ ) );

    // Fills the image buffer with zeroes (black)
    for ( std::size_t y = 0; y < v_resolution_; y++ )
        for ( std::size_t x = 0; x < h_resolution_; x++ )
            buffer_data_[x][y] = glm::vec3{ 0.0f, 0.0f, 0.0f };
}

Buffer::~Buffer( void )
{}

void Buffer::save( const std::string &filename ) const
{
    std::clog << "Buffer saving started... ";

    std::ofstream rendering_file;

    rendering_file.open(filename.c_str());

    // Header of the PPM file. More on this filetype in:
    //     http://netpbm.sourceforge.net/doc/ppm.html
    rendering_file << "P3"
                   << std::endl
                   << h_resolution_
                   << " "
                   << v_resolution_
                   << std::endl
                   << 255
                   << std::endl;

    // Writes color data to the output PPM file
    for ( unsigned int y = 0; y < v_resolution_; y++ )
    {
        for ( unsigned int x = 0; x < h_resolution_; x++ )
        {
            // convert from real to [0.0, 1.0] with clamp, then
            //         from [0.0, 1.0] to [0.0, 255.0], then
            //         from [0.0, 255.0] to [0.5, 255.5], then
            //         from [0.5, 255.5] to [0, 255] with round to nearest.
            glm::vec3 color(buffer_data_[x][y]);
            color = glm::convertLinearToSRGB(color);
            rendering_file << static_cast<int>(clamp(color.r) * 255.0f + 0.5f) << " ";
            rendering_file << static_cast<int>(clamp(color.g) * 255.0f + 0.5f) << " ";
            rendering_file << static_cast<int>(clamp(color.b) * 255.0f + 0.5f) << " ";
        }
    }

    rendering_file.close();

    std::clog << "finished!\n";
}

