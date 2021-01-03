#include "runner.h"

#include <string>

bool runner::bake(std::ifstream cfg) {
    if (!cfg.is_open()) {
        return false;
    }

    system("mkdir runners/src/");
    int number;
    std::string word;
    while (cfg >> word) {
        // unsaved changes, need to bake
        if (word == "*\"") {
            std::string name;
            while (word != "\"") {
                cfg >> word;
                name += word;
                name += " ";
            }
            name = name.substr(0, name.size() - 3);
            std::ofstream dest("runners/src/" + name + ".cpp");
            if (!dest.is_open()) {
                return false;
            }

            /*** WRITE START { ***/
            dest << "#include <random>\n";
            dest << "#include <iostream>\n";

            // representation of a second
            dest << "int const SECOND_ = 1000;";

            /** parameters baked in { **/
            // verbose level 0, 1, 2, 10
            cfg >> number;
            if (number >= 10) {
              dest << "\n#define VERBOSE_DEVELOPER\n";
            } else if (number >= 2) {
                dest << "#define VERBOSE_MORE\n";
            } else if (number >= 1) {
                dest << "#define VERBOSE_REGULAR\n";
            } else if (!number) {
                dest << "#define VERBOSE_MINIMAL\n";
            }
            // button for xdotool to inject
            cfg >> number;
            dest << "int const BUTTON = " << number << ";";
            // min/max cps/delay (range for min cps and max cps can be configured)
            // NOTE: delay delta = absolute, cps delta = relative, % delta = relative
            cfg >> number;
            dest << "int const MIN_MIN_CPS = " << number << ";";
            cfg >> number;
            dest << "int const MAX_MIN_CPS = " << number << ";";
            cfg >> number;
            dest << "int const MIN_MAX_CPS = " << number << ";";
            cfg >> number;
            dest << "int const MAX_MAX_CPS = " << number << ";";
            cfg >> number;
            dest << "int const MIN_MIN_DELAY_DELTA = " << number << ";";
            cfg >> number;
            dest << "int const MAX_MIN_DELAY_DELTA = " << number << ";";
            cfg >> number;
            dest << "int const MIN_MAX_DELAY_DELTA = " << number << ";";
            cfg >> number;
            dest << "int const MAX_MAX_DELAY_DELTA = " << number << ";";
            // current it's cps/delay
            cfg >> number;
            dest << "int const MIN_DELAY_DELTA = " << number << ";";
            cfg >> number;
            dest << "int const MAX_DELAY_DELTA = " << number << ";";
            // its to next regen
            cfg >> number;
            dest << "int const MIN_TO_RECALC = " << number << ";";
            cfg >> number;
            dest << "int const MAX_TO_RECALC = " << number << ";";
            cfg >> number;
            dest << "int const MIN_TO_RECALC_DELTA = " << number << ";";
            cfg >> number;
            dest << "int const MAX_TO_RECALC_DELTA = " << number << ";";
            // its to clamping of inner gen loop
            cfg >> number;
            dest << "int const MIN_TO_CLAMP = " << number << ";";
            cfg >> number;
            dest << "int const MAX_TO_CLAMP = " << number << ";";
            /** parameters baked in fin } **/

          dest << "\n#ifdef VERBOSE_DEVELOPER\n";
            dest << "#define VERBOSE_MORE\n";
            dest << "#endif\n";
            dest << "#ifdef VERBOSE_MORE\n";
            dest << "#define VERBOSE_REGULAR\n";
            dest << "#endif\n";
            dest << "#ifdef VERBOSE_REGULAR\n";
            dest << "#define VERBOSE_MINIMAL\n";
            dest << "#endif\n";

            dest << "std::random_device real_rand;";
            dest << "std::mt19937 ps_rand{real_rand()};";

            dest << "inline int __attribute ((always_inline)) rng(int const lower, int const upper) {";
                dest << "std::uniform_int_distribution<> dist(lower, upper);";
                dest << "return dist(ps_rand);";
            dest << "}";

            dest << "inline void __attribute ((always_inline)) regen(int &cur, int const prev, int const thres, int const begin, int const end, int const type, char const label) {";
                dest << "int its = 0;";
                dest << "while (abs(cur - prev) < thres) {";
                    dest << "if (its > rng(MIN_TO_CLAMP, MAX_TO_CLAMP)) {";
          dest << "\n#       ifdef VERBOSE_DEVELOPER\n";
                        dest << "std::cout << \"C <----------------------------------------------- Clamped !!\" << std::endl;";
          dest << "\n#       endif\n";
                        dest << "break;";
                    dest << "}";
          dest << "\n#   ifdef VERBOSE_DEVELOPER\n";
                    dest << "std::cout << label;";
          dest << "\n#   endif\n";
                    dest << "if (!type) {";
                        dest << "cur = rng(begin, end);";
                    dest << "} else {";
                        dest << "cur = round((double) SECOND_ / rng(begin, end));";
                    dest << "}";
                    dest << "its++;";
                dest << "}";
          dest << "\n#ifdef VERBOSE_DEVELOPER\n";
                dest << "std::cout << std::endl;";
          dest << "\n#endif\n";
            dest << "}";

            dest << "int main() {";
                dest << "std::string button_str = std::to_string(BUTTON);";
                dest << "int prev_min_delay = round((double) SECOND_ / rng(MIN_MAX_CPS, MAX_MAX_CPS));";
                dest << "int prev_max_delay = round((double) SECOND_ / rng(MIN_MIN_CPS, MAX_MIN_CPS));";
                dest << "int prev_min_delay_delta = rng(MIN_MAX_DELAY_DELTA, MAX_MAX_DELAY_DELTA);";
                dest << "int prev_max_delay_delta = rng(MIN_MIN_DELAY_DELTA, MAX_MIN_DELAY_DELTA);";
                dest << "int min_delay = prev_min_delay;";
                dest << "int max_delay = prev_max_delay;";
                dest << "int min_delay_delta = prev_min_delay_delta;";
                dest << "int max_delay_delta = prev_max_delay_delta;";
                dest << "int prev_to_recalc = rng(MIN_TO_RECALC, MAX_TO_RECALC);";
                dest << "int prev_to_recalc_delta = rng(MIN_TO_RECALC_DELTA, MAX_TO_RECALC_DELTA);";
                dest << "int to_recalc = prev_to_recalc;";
                dest << "int to_recalc_delta = prev_to_recalc_delta;";
                dest << "int prev_delay = rng(min_delay, max_delay);";
                dest << "int prev_delay_delta = rng(MIN_DELAY_DELTA, MAX_DELAY_DELTA);";
                dest << "int its = 0;";
                dest << "while (true) {";
                    dest << "if (its == to_recalc) {";
                        dest << "regen(min_delay_delta, prev_min_delay_delta, 1, MIN_MAX_DELAY_DELTA, MAX_MAX_DELAY_DELTA, 0, 'l');";
                        dest << "regen(max_delay_delta, prev_max_delay_delta, 1, MIN_MIN_DELAY_DELTA, MAX_MIN_DELAY_DELTA, 0, 'u');";
                        dest << "regen(min_delay, prev_min_delay, min_delay_delta, MIN_MAX_CPS, MAX_MAX_CPS, 1, 'L');";
                        dest << "regen(max_delay, prev_max_delay, max_delay_delta, MIN_MIN_CPS, MAX_MIN_CPS, 1, 'U');";
                        dest << "regen(to_recalc_delta, prev_to_recalc_delta, 1, MIN_TO_RECALC_DELTA, MAX_TO_RECALC_DELTA, 0, 'r');";
                        dest << "regen(to_recalc, prev_to_recalc, to_recalc_delta, MIN_TO_RECALC, MAX_TO_RECALC, 0, 'R');";
          dest << "\n#       ifdef VERBOSE_REGULAR\n";
                        dest << "std::cout << \">>>>>>> ({ RECALCULATED }) <<<<<<<\" << std::endl;";
                        dest << "std::cout << \"min_cps: \" << SECOND_ / max_delay << \", max_cps: \" << SECOND_ / min_delay << '\\n' << std::endl;";
          dest << "\n#       endif\n";
                        dest << "prev_min_delay_delta = min_delay_delta;";
                        dest << "prev_max_delay_delta = max_delay_delta;";
                        dest << "prev_min_delay = min_delay;";
                        dest << "prev_max_delay = max_delay;";
                        dest << "prev_to_recalc_delta = to_recalc_delta;";
                        dest << "prev_to_recalc = to_recalc;";
                        dest << "its = 0;";
                    dest << "}";
                    dest << "int delay_delta = prev_delay_delta;";
                    dest << "int delay = prev_delay;";
                    dest << "regen(delay_delta, prev_delay_delta, 1, MIN_DELAY_DELTA, MAX_DELAY_DELTA, 0, 'd');";
                    dest << "regen(delay, prev_delay, delay_delta, min_delay, max_delay, 0, 'D');";

                    dest << "std::string call;";
                    dest << "call += \"xdotool click --delay \";";
                    dest << "call += std::to_string(delay);";
                    dest << "call += ' ';";
                    dest << "call += button_str;";
          dest << "\n#   ifdef VERBOSE_MORE\n";
                    dest << "std::cout << delay << std::endl;";
          dest << "\n#   endif\n";
            dest << "#   ifdef VERBOSE_REGULAR\n";
                    dest << "std::cout << '[' << (double) SECOND_ / delay << ']' << '\\n' << std::endl;";
          dest << "\n#   endif\n";
                    dest << "system(call.c_str());";
                    dest << "prev_delay_delta = delay_delta;";
                    dest << "prev_delay = delay;";
                    dest << "its++;";
                dest << "}";
            dest << "}" << std::endl;
            /*** WRITE FINISH } ***/
            // now compile
            std::string call;
            call += "g++ -std=c++20 -Ofast \"runners/src/";
            call += name;
            call += ".cpp\" -o \"runners/";
            call += name;
            call += "\"";
            system(call.c_str());
        } else {
            // skip
            for (int i = 0; i < 18; i++) {
                cfg >> word;
            }
        }
    }

    return true;
}
