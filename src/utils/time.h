#pragma once

#include <chrono>

namespace utils::time {
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;

    timestamp cur();
    int diff(timestamp const &later, timestamp const &earlier, bool microseconds);
}
