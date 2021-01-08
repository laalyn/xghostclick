#pragma once

#include "utils/input.h"

#include <vector>
#include <string>

namespace settings {
    struct entry {
        enum trigger {
            HOLD,
            TOGGLE,
        };

        struct input {
            utils::input::type type;
            int state_id;
        };

        struct match {
            bool down;
            entry::input input;
        };

        struct range {
            int min, max;
        };

        struct range_d {
            int min_delta, max_delta;
        };

        struct drange { // double range
            int min, max;
            int min_delta, max_delta;
        };

        trigger trigger;
        std::vector<match> match;
        input control;
        drange min_speed, max_speed; // row 1: cps, row 2: delay (ms)
        range_d delay;
        drange percent_down;
        drange to_recalc;
        range to_clamp;
        // deprecated in favor of above
        // int min_min_cps, max_min_cps;
        // int min_max_cps, max_max_cps;
        // int min_min_delay_delta, max_min_delay_delta;
        // int min_max_delay_delta, max_max_delay_delta;
        // int min_delay_delta, max_delay_delta;
        // int min_percent_down, max_percent_down;
        // int min_percent_down_delta, max_percent_down_delta;
        // int min_to_recalc, max_to_recalc;
        // int min_to_recalc_delta, max_to_recalc_delta;
        // int min_to_clamp, max_to_clamp;
    };

    // global settings
    inline int verbosity = 0;
    inline int precision = 1000; // microseconds
    inline bool could_achieve_precision = false;
    inline int keyboard_id;
    inline int pointer_id;
    inline std::vector<entry> entries;

    bool load(std::string const &path);
}