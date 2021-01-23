#include "input.h"
#include "../settings.h"

#include <cstdio>
#include <string>
#include <iostream>

using namespace utils::input;

void utils::input::list_devices() {
    system("xinput");
}

bool utils::input::is_down(int const state_id, int const device_id, type const type) {
    std::string cmd("xinput --query-state ");
    cmd += std::to_string(device_id);
    cmd += " | grep \"";
    cmd += type ? "button" : "key";
    cmd += "\\[";
    cmd += std::to_string(state_id);
    cmd += "\\]\"";

    FILE *pipe = popen(cmd.c_str(), "r");

    char buf[32];
    char *ret_cstr = fgets(buf, sizeof buf, pipe);

    fclose(pipe); // <-- fixes segfault

    std::string ret(ret_cstr);
    if (ret.substr(ret.size() - 5, 4) == "down") {
        return true;
    }

    return false;
}

void utils::input::send(int const state_id, type const type, bool const down) {
    std::string cmd("xdotool");
    cmd += type ? (down ? " mousedown " : " mouseup ") : (down ? " keydown " : " keyup ");
    cmd += std::to_string(state_id);

    if (settings::verbosity >= 10) {
        std::cout << "state is " << down << std::endl;
    }

    system(cmd.c_str());
}
