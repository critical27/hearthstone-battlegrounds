#pragma once

#include <random>

// random num in [min, max]
static size_t rand(size_t min, size_t max) {
    std::uniform_int_distribution<size_t > dist(min, max);
    std::random_device rd;
    std::default_random_engine engine{rd()};
    return dist(engine);
}
