#include "time.h"

using namespace utils::time;

timestamp utils::time::cur() {
    return std::chrono::high_resolution_clock::now();
}

int utils::time::diff(timestamp const &later, timestamp const &earlier, bool microseconds) {
    if (microseconds) {
        return std::chrono::duration_cast<std::chrono::microseconds>(later - earlier).count();
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(later - earlier).count();
}
