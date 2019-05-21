#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>

class Buffer {
public:
    Buffer();
    Buffer(unsigned w, unsigned h);
    ~Buffer();

    void save(const std::string &filename) const;

    unsigned int width_ = 512;

    unsigned int height_ = 512;

    std::vector<std::vector<glm::vec3>> buffer_data_;
};
