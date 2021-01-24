#include "psrand.h"

#include <random>

using namespace utils::psrand;

std::random_device real_rand;
std::mt19937 ps_rand(real_rand());

int utils::psrand::gen(int const lower, int const upper) {
    std::uniform_int_distribution<> dist(lower, upper);
    return dist(ps_rand);
}
