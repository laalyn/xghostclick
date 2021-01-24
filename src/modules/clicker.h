#pragma once

#include "../utils/time.h"

#include <unordered_map>

namespace modules::clicker {
    int const SECOND = 1000;

    struct state {
        struct drange {
            int prev = 0; // prev_delay needs this to be 0
            int prev_delta;
            int cur = prev;
            int cur_delta = prev_delta;
        };

        // toggle mode only, hold mode ignores these
        bool on = false, reset = true;

        bool sent_down = false, up_on_quit = false;
        utils::time::timestamp last_send = utils::time::cur();
        drange min_delay, max_delay, delay;
        drange percent_down;
        drange to_recalc;
        int its = 0;
    };

    inline std::unordered_map<int, state> entries;

    void send_input();
}
