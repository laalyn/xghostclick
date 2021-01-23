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
        // deprecated in favor of above
        // int prev_min_delay, prev_max_delay;
        // int prev_min_delay_delta, prev_max_delay_delta;
        // int min_delay = prev_min_delay, max_delay = prev_max_delay;
        // int min_delay_delta = prev_min_delay_delta, max_delay_delta = prev_max_delay_delta;
        // int prev_delay = 0, prev_delay_delta;
        // int delay = prev_delay, delay_delta = prev_delay_delta;
        // int prev_percent_down, prev_percent_down_delta;
        // int percent_down = prev_percent_down, percent_down_delta = prev_percent_down_delta;
        // int prev_to_recalc, prev_to_recalc_delta;
        // int to_recalc = prev_to_recalc, to_recalc_delta = prev_to_recalc_delta;
        int its = 0;
    };

    inline std::unordered_map<int, state> entries;

    void send_input();
}
