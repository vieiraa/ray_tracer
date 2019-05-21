#pragma once

#include <random>

class Random {
    std::random_device device;
    std::uniform_real_distribution<float> dist;
    float seed;
    std::mt19937 rng;

public:
    Random();

    float get();
};
