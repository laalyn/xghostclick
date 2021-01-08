#include "settings.h"

#include <iostream>
#include <fstream>

using namespace settings;

bool settings::load(std::string const &path) {
    if (path.empty()) {
        std::cout << "ERROR: you did not specify a config file" << std::endl;
        return false;
    }

    std::ifstream file(path.c_str());
    if (!file.is_open()) {
        std::cout << "ERROR: specified config file does not exist" << std::endl;
        return false;
    }

    // now read from file
    bool keyboard_id_picker = true, mouse_id_picker = true;
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
                keyboard_id_picker = false;
            } else if (word == "pointer_id") {
                file >> number;
                pointer_id = number;
                mouse_id_picker = false;
            } else {
                std::cout << "ERROR: The config file specified has a problem. Please double-check syntax." << std::endl;
                return false;
            }
        // write an entry
        } else if (word == "!ENTRY") {
            if (keyboard_id_picker || mouse_id_picker) {
                utils::input::list_devices();

                if (keyboard_id_picker) {
                    std::cout << "\npick id for keyboard: " << std::flush;
                    std::cin >> keyboard_id;
                    keyboard_id_picker = false;
                }

                if (mouse_id_picker) {
                    std::cout << "pick id for pointer: " << std::flush;
                    std::cin >> pointer_id;
                    mouse_id_picker = false;
                }

                std::cout << std::endl;
            }

            entry entry;
            file >> word;
            entry.trigger = word == "toggle" ? entry::TOGGLE : entry::HOLD;
            while (file >> word) {
                if (word == ";") {
                    break;
                }

                struct entry::match match;
                match.down = word == "down";
                file >> word;
                match.input.type = word == "key" ? utils::input::KEY : utils::input::BUTTON;
                file >> number;
                match.input.state_id = number;

                entry.match.emplace_back(match);
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

            entries.emplace_back(entry);
        }
    }

    return true;
}