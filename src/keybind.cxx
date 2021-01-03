#include <random>

std::random_device real_rand;
std::mt19937 ps_rand{real_rand()};

inline int __attribute ((always_inline)) rng(int const lower, int const upper) {
    std::uniform_int_distribution<> dist(lower, upper);
    return dist(ps_rand);
}
