#include "settings.h"
#include "utils/hooker.h"
#include "hooks/send_input.h"

#include <iostream>

int main(int const argc, char const *argv[]) {
    std::vector<std::string> paths;
    for (int i = 1; i < argc; i++) {
        std::string word(argv[i]);
        if (word.find('/') != std::string::npos || word.find('.') != std::string::npos) {
            paths.emplace_back(word);
        } else {
            std::string path("config/");
            path += word;
            path += ".txt";
            paths.emplace_back(path);
        }
    }

    if (!settings::load(paths)) {
        return 1;
    }

    utils::hooker::hook(hooks::send_input::start);
    std::cout << "Started. Press ^C to stop\n" << std::endl;

    // wait for ^C
    while (true);
}
