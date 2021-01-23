#include "hooker.h"
#include "../settings.h"

#include <thread>
#include <iostream>

using namespace utils::hooker;

void utils::hooker::hook(std::function<void()> const &func) {
    std::thread thread(func);
    thread.detach();
}

void utils::hooker::enforce_precision(int const microseconds, int const ofs) {
    if (!microseconds) {
        return;
    }

    if (microseconds - ofs < 0) {
        if (settings::verbosity >= 1) {
            std::cout << "WARNING: couldn't achieve specified precision level! maybe set it above " << ofs << "?" << std::endl;
        }

        return;
    }

    std::this_thread::sleep_for(std::chrono::microseconds(microseconds - ofs));
}