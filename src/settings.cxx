#include "settings.h"

#include <iostream>
#include <fstream>

using namespace settings;

bool settings::load(std::vector<std::string> const &paths) {
    if (paths.empty()) {
        std::cerr << "ERROR: you did not specify a config file" << std::endl;
        return false;
    }

    for (auto &s: paths) {
        std::ifstream file(s);
        if (!file.is_open()) {
            std::cerr << "ERROR: specified config file does not exist" << std::endl;
            return false;
        }

        // now read from file
        int number;
        std::string word;
        // wait for special stuff
        while (file >> word) {
            // write a global setting
            if (word == "!GLOBAL") {
                file >> word;
                if (word == "verbosity") {
                    file >> number;
                    verbosity = number;
                } else if (word == "precision") {
                    file >> number;
                    precision = number;
                } else if (word == "keyboard_id") {
                    file >> number;
                    keyboard_id = number;
                } else if (word == "pointer_id") {
                    file >> number;
                    pointer_id = number;
                } else {
                    std::cerr << "ERROR: The config file specified has a problem. Please double-check syntax." << std::endl;
                    return false;
                }
            // write an entry
            } else if (word == "!ENTRY") {
                if (keyboard_id == -1 || pointer_id == -1) {
                    utils::input::list_devices();

                    if (keyboard_id == -1) {
                        std::cout << "\npick id for keyboard: " << std::flush;
                        std::cin >> keyboard_id;
                    }

                    if (pointer_id == -1) {
                        std::cout << "pick id for pointer: " << std::flush;
                        std::cin >> pointer_id;
                    }

                    std::cout << std::endl;
                }

                clicker::entry entry;
                file >> word;
                entry.trigger = word == "toggle" ? clicker::entry::TOGGLE : clicker::entry::HOLD;
                enum phase {
                    TRIGGER,
                    INTERRUPT,
                    RESUME,
                };
                phase phase = TRIGGER;
                while (file >> word && word != ";") {
                    // TODO: add override options for AND and OR

                    if (word == "interrupt" || word == "resume") {
                        if (word == "interrupt") {
                            phase = INTERRUPT;
                        } else if (word == "resume") {
                            phase = RESUME;
                        }

                        continue;
                    }

                    if (!phase) {
                        struct clicker::entry::match match;
                        match.down = word == "down";
                        file >> word;
                        match.input.type = word == "key" ? utils::input::KEY : utils::input::BUTTON;
                        file >> number;
                        match.input.state_id = number;

                        entry.match.emplace_back(match);
                    } else if (phase == INTERRUPT) {
                        struct clicker::entry::input_p interrupt;
                        interrupt.type = word == "keys" ? utils::input::KEY : utils::input::BUTTON;
                        file >> number;
                        interrupt.state_id_range.first = number;
                        file >> number;
                        interrupt.state_id_range.second = number;

                        entry.interrupt.emplace_back(interrupt);
                    } else {
                        struct clicker::entry::input resume;
                        resume.type = word == "key" ? utils::input::KEY : utils::input::BUTTON;
                        file >> number;
                        resume.state_id = number;

                        entry.resume.emplace_back(resume);
                    }
                }

                file >> word;
                entry.control.type = word == "key" ? utils::input::KEY : utils::input::BUTTON;
                file >> number;
                entry.control.state_id = number;
                file >> number;
                entry.min_speed.min = number;
                file >> number;
                entry.min_speed.max = number;
                file >> number;
                entry.max_speed.min = number;
                file >> number;
                entry.max_speed.max = number;
                file >> number;
                entry.min_speed.min_delta = number;
                file >> number;
                entry.min_speed.max_delta = number;
                file >> number;
                entry.max_speed.min_delta = number;
                file >> number;
                entry.max_speed.max_delta = number;
                file >> number;
                entry.delay.min_delta = number;
                file >> number;
                entry.delay.max_delta = number;
                file >> number;
                entry.percent_down.min = number;
                file >> number;
                entry.percent_down.max = number;
                file >> number;
                entry.percent_down.min_delta = number;
                file >> number;
                entry.percent_down.max_delta = number;
                file >> number;
                entry.to_recalc.min = number;
                file >> number;
                entry.to_recalc.max = number;
                file >> number;
                entry.to_recalc.min_delta = number;
                file >> number;
                entry.to_recalc.max_delta = number;
                file >> number;
                entry.to_clamp.min = number;
                file >> number;
                entry.to_clamp.max = number;

                clicker::entries.emplace_back(entry);
            }
        }
    }

    return true;
}