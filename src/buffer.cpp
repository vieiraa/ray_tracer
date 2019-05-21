#include "buffer.h"
#include <glm/gtc/color_space.hpp>

inline float clamp(float x) {
    return (x < 0.0f) ? 0.0f : (x > 1.0f) ? 1.0f : x;
}

Buffer::Buffer() {
    buffer_data_.resize(width_, std::vector<glm::vec3>(height_) );

    for (unsigned y = 0; y < height_; y++)
        for (unsigned x = 0; x < width_; x++ )
            buffer_data_[x][y] = glm::vec3{ 0.0f, 0.0f, 0.0f };
}

Buffer::Buffer(unsigned w, unsigned h) :
    width_(w),
    height_(h)
{
    buffer_data_.resize(width_, std::vector<glm::vec3>(height_));

    for (std::size_t y = 0; y < height_; y++ )
        for (std::size_t x = 0; x < width_; x++ )
            buffer_data_[x][y] = glm::vec3(0.0f);
}

Buffer::~Buffer() {}

void Buffer::save(const std::string &filename) const {
    std::clog << "Buffer saving started... ";

    std::ofstream rendering_file;

    rendering_file.open(filename.c_str());

    // Header of the PPM file. More on this filetype in:
    //     http://netpbm.sourceforge.net/doc/ppm.html
    rendering_file << "P3"
                   << std::endl
                   << width_
                   << " "
                   << height_
                   << std::endl
                   << 255
                   << std::endl;

    // Writes color data to the output PPM file
    for (unsigned y = 0; y < height_; y++) {
        for (unsigned x = 0; x < width_; x++) {
            glm::vec3 color(buffer_data_[x][y]);
            color = glm::convertLinearToSRGB(color);
            rendering_file << static_cast<int>(clamp(color.r) * 255.0f + 0.5f) << " ";
            rendering_file << static_cast<int>(clamp(color.g) * 255.0f + 0.5f) << " ";
            rendering_file << static_cast<int>(clamp(color.b) * 255.0f + 0.5f) << " ";
        }

        rendering_file << "\n";
    }

    rendering_file.close();

    std::clog << "finished!\n";
}
