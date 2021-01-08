#include "settings.h"
#include "utils/hooker.h"
#include "hooks/send_input.h"

#include <iostream>

int main(int const argc, char const *argv[]) {
    if (!settings::load(argc == 1 ? "" : argv[argc - 1])) {
        return 1;
    }

    utils::hooker::hook(hooks::send_input::start);
    std::cout << "Started. Press ^C to stop\n" << std::endl;

    // wait for ^C
    while (true);
}
