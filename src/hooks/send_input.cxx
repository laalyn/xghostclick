#include "send_input.h"
#include "../modules/clicker.h"
#include "../utils/hooker.h"
#include "../settings.h"

#include <iostream>

using namespace hooks::send_input;

void hooks::send_input::start() {
    while (true) {
        utils::time::timestamp st = utils::time::cur();
        modules::clicker::send_input();
        utils::time::timestamp end = utils::time::cur();
        if (settings::verbosity >= 100) {
            std::cout << "cycle: " << utils::time::diff(end, st, true) << " microseconds" << std::endl;
        }

        utils::hooker::enforce_precision(settings::precision, utils::time::diff(end, st, true));
    }
}