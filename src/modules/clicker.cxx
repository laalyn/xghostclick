#include "clicker.h"
#include "../settings.h"
#include "../utils/psrand.h"

#include <cmath>
#include <iostream>

using namespace modules::clicker;

void regen(int &cur, int const prev, int const thres, int const lower, int const upper, int const type, int const entry_idx, char const label) {
    int clamp = utils::psrand::gen(settings::entries[entry_idx].to_clamp.min, settings::entries[entry_idx].to_clamp.max);
    int its = 0;
    while (abs(cur - prev) < thres) {
        if (its > clamp) {
            if (settings::verbosity >= 10) {
                std::cout << "C <----------------------------------------------- Clamped !!" << std::endl;
            }

            break;
        }

        if (settings::verbosity >= 10) {
            std::cout << label;
        }

        if (!type) {
            cur = utils::psrand::gen(lower, upper);
        } else {
            cur = round((double) SECOND / utils::psrand::gen(lower, upper));
        }

        its++;
    }

    if (settings::verbosity >= 10) {
        std::cout << std::endl;
    }
}

void modules::clicker::send_input() {
    for (int i = 0; i < settings::entries.size(); i++) {
        // input matching
        bool matched = true;
        for (auto &m: settings::entries[i].match) {
            if (utils::input::is_down(m.input.state_id, m.input.type ? settings::pointer_id : settings::keyboard_id, m.input.type) != m.down) {
                matched = false;
                break;
            }
        }

        // hold: if match: run
        // toggle: if match: if reset: flip on
        if (!matched) {
            if (settings::entries[i].trigger) {
                entries[i].reset = true;
            } else {
                continue;
            }
        }

        if (settings::entries[i].trigger && entries[i].reset && matched) {
            entries[i].on = !entries[i].on;
            entries[i].reset = false;
        }

        if (settings::entries[i].trigger && !entries[i].on) {
            if (entries[i].up_on_quit) {
                utils::input::send(settings::entries[i].control.state_id, settings::entries[i].control.type, false);
                entries[i].up_on_quit = false;
            }
            continue;
        }

        entries[i].up_on_quit = true;

        if (!entries[i].sent_down && utils::time::diff(utils::time::cur(), entries[i].last_send, false) < round((double) entries[i].delay.cur * entries[i].percent_down.cur * 0.01)) {
            continue;
        }

        if (entries[i].sent_down && utils::time::diff(utils::time::cur(), entries[i].last_send, false) < entries[i].delay.cur) {
            continue;
        }

        // now we start
        // send the input
        utils::input::send(settings::entries[i].control.state_id, settings::entries[i].control.type, !entries[i].sent_down);
        entries[i].last_send = utils::time::cur();
        if (!entries[i].sent_down) {
            entries[i].sent_down = true;
            continue;
        }
        entries[i].sent_down = false;
        // then regen
        // outer scope humanization
        if (entries[i].its == entries[i].to_recalc.cur) {
            regen(entries[i].min_delay.cur_delta, entries[i].min_delay.prev_delta, 1, settings::entries[i].min_speed.min_delta, settings::entries[i].min_speed.max_delta, 0, i, 'l');
            regen(entries[i].max_delay.cur_delta, entries[i].max_delay.prev_delta, 1, settings::entries[i].max_speed.min_delta, settings::entries[i].max_speed.max_delta, 0, i, 'u');
            regen(entries[i].min_delay.cur, entries[i].min_delay.prev, entries[i].min_delay.cur_delta, settings::entries[i].max_speed.min, settings::entries[i].max_speed.max, 1, i, 'L');
            regen(entries[i].max_delay.cur, entries[i].max_delay.prev, entries[i].max_delay.cur_delta, settings::entries[i].min_speed.min, settings::entries[i].min_speed.max, 1, i, 'U');
            regen(entries[i].to_recalc.cur_delta, entries[i].to_recalc.prev_delta, 1, settings::entries[i].to_recalc.min_delta, settings::entries[i].to_recalc.max_delta, 0, i, 'r');
            regen(entries[i].to_recalc.cur, entries[i].to_recalc.prev, entries[i].to_recalc.cur_delta, settings::entries[i].to_recalc.min, settings::entries[i].to_recalc.max, 0, i, 'R');

            if (settings::verbosity >= 2) {
                std::cout << ">>>>>>> {( min_cps: " << SECOND / entries[i].max_delay.cur << ", max_cps: " << SECOND / entries[i].min_delay.cur << ")} <<<<<<<\n" << std::endl;
            }

            entries[i].min_delay.prev_delta = entries[i].min_delay.cur_delta;
            entries[i].max_delay.prev_delta = entries[i].max_delay.cur_delta;
            entries[i].min_delay.prev = entries[i].min_delay.cur;
            entries[i].max_delay.prev = entries[i].max_delay.cur;
            entries[i].to_recalc.prev_delta = entries[i].to_recalc.cur_delta;
            entries[i].to_recalc.prev = entries[i].to_recalc.cur;
            entries[i].its = 0;
        }

        // inner scope humanization
        regen(entries[i].delay.cur_delta, entries[i].delay.prev_delta, 1, settings::entries[i].delay.min_delta, settings::entries[i].delay.max_delta, 0, i, 'd');
        regen(entries[i].delay.cur, entries[i].delay.prev, entries[i].delay.cur_delta, entries[i].min_delay.cur, entries[i].max_delay.cur, 0, i, 'D');
        regen(entries[i].percent_down.cur_delta, entries[i].percent_down.prev_delta, 1, settings::entries[i].percent_down.min_delta, settings::entries[i].percent_down.max_delta, 0, i, 'p');
        regen(entries[i].percent_down.cur, entries[i].percent_down.prev, entries[i].percent_down.cur_delta, settings::entries[i].percent_down.min, settings::entries[i].percent_down.max, 0, i,  'P');

        if (settings::verbosity >= 3) {
            std::cout << entries[i].delay.cur << ' ' << round((double) entries[i].delay.cur * entries[i].percent_down.cur * 0.01) << std::endl;
        }

        if (settings::verbosity >= 1) {
            std::cout << '[' << (double) SECOND / entries[i].delay.cur << "cps, " << entries[i].percent_down.cur << "%]\n" << std::endl;
        }

        entries[i].delay.prev_delta = entries[i].delay.cur_delta;
        entries[i].delay.prev = entries[i].delay.cur;
        entries[i].percent_down.prev_delta = entries[i].percent_down.cur_delta;
        entries[i].percent_down.prev = entries[i].percent_down.cur;
        entries[i].its++;
    }
}