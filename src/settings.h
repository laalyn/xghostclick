#pragma once

#include "utils/input.h"

#include <vector>
#include <string>

namespace settings {
    namespace clicker {
        struct entry {
            enum trigger {
                HOLD,
                TOGGLE,
            };

            struct input {
                utils::input::type type;
                int state_id;
            };

            struct input_p {
                utils::input::type type;
                std::pair<int, int> state_id_range;
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
            std::vector<input_p> interrupt;
            std::vector<input> resume;
            input control;
            drange min_speed, max_speed; // row 1: cps, row 2: delay (ms)
            range_d delay;
            drange percent_down;
            drange to_recalc;
            range to_clamp;
        };

        inline std::vector<entry> entries;
    }

    // global settings
    inline int verbosity = 0;
    inline int precision = 1000; // microseconds
    inline int keyboard_id = -1;
    inline int pointer_id = -1;

    bool load(std::vector<std::string> const &paths);
}