#pragma once

#include <functional>

namespace utils::hooker {
    void hook(std::function<void()> const &func);
    void enforce_precision(int microseconds, int ofs);
}