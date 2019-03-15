#include "random.h"

Random::Random() {
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng = std::mt19937(seed);
}

float Random::get() {
    auto ret = dist(rng);
    return ret;
}
