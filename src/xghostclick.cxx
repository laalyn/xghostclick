#include "runner.h"

#include <random>
#include <iostream>
#include <unordered_set>

int main(int const argc, char const *argv[]) {
    system("mkdir runners");
    system("touch runners.txt keybinds.txt settings.txt");
    system("clear");
    std::cout << "XGHOSTCLICK, The Undetected Autoclicker [github.com/laalyn/xghostclick]\n" << std::endl;

    std::unordered_set<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.emplace(argv[i]);
    }

    if (args.find("--serve") != args.end()) {
        goto SERVE;
    }

    char inp;

    MAIN:;
    system("clear");
    std::cout << "[XGHOSTCLICK] -----------------------------------------------------------" << std::endl;
    if (args.find("--interactive") == args.end()) {
        std::cout << "No valid arguments specified, running in interactive mode (--interactive)\n" << std::endl;
    }
    std::cout << "l - Launch xghostclick keybind server (--serve)" << std::endl;
    std::cout << "r - Manage runners" << std::endl;
    std::cout << "k - Edit keybinds" << std::endl;
    std::cout << "s - Change settings" << std::endl;
    std::cout << "q - Quit (or ^C)" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    while (true) {
        std::cout << "select one: " << std::flush;
        std::cin >> inp;
        if (inp == 'l') {
            goto SERVE;
        } else if (inp == 'r') {
            goto RUNNERS;
        } else if (inp == 'k') {
            goto KEYBINDS;
        } else if (inp == 's') {
            goto SETTINGS;
        } else if (inp == 'q') {
            goto QUIT;
        } else {
            std::cout << "invalid selection!" << std::endl;
        }
    }

    {
        RUNNERS:;
        system("clear");
        std::cout << "[XGHOSTCLICK] -> Runners ------------------------------------------------" << std::endl;
        // placeholder
        // std::cout << "Configured runners:" << std::endl;
        // std::cout << "<0> \"pvp\"" << std::endl;
        // std::cout << "<1> \"bridge\"" << std::endl;
        // std::cout << "<2> \"fast pvp\" *" << std::endl;
        // std::cout << "<3> \"godbridge\" *\n" << std::endl;
        // ---
        std::cout << "w - Apply changes (regenerates runners)" << std::endl; // dynamically appearing
        // std::cout << "p [i] - List properties of runner by id *" << std::endl;
        // std::cout << "l [s] - List properties of runner by name *" << std::endl;
        // std::cout << "x [i] - Remove runner by id *" << std::endl;
        // std::cout << "r [s] - Remove runner by name *" << std::endl;
        // std::cout << "a [s] - Add runner under a name *" << std::endl;
        std::cout << "b - Go back" << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        while (true) {
            std::cout << "select one: " << std::flush;
            std::cin >> inp;
            if (inp == 'w') {
                runner::bake(std::ifstream("runners.txt"));
                goto RUNNERS;
            } else if (inp == 'b') {
                goto MAIN;
            } else {
                std::cout << "invalid selection!" << std::endl;
            }
        }

        KEYBINDS:;
        system("clear");
        std::cout << "[XGHOSTCLICK] -> Keybinds -----------------------------------------------" << std::endl;
        std::cout << "b - Go back" << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        while (true) {
            std::cout << "select one: " << std::flush;
            std::cin >> inp;
            if (inp == 'b') {
                goto MAIN;
            } else {
                std::cout << "invalid selection!" << std::endl;
            }
        }

        SETTINGS:;
        system("clear");
        std::cout << "[XGHOSTCLICK] -> Settings -----------------------------------------------" << std::endl;
        std::cout << "b - Go back" << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        while (true) {
            std::cout << "select one: " << std::flush;
            std::cin >> inp;
            if (inp == 'b') {
                goto MAIN;
            } else {
                std::cout << "invalid selection!" << std::endl;
            }
        }
    }

    QUIT:;
    system("clear");
    std::cout << "Quit." << std::endl;
    return 0;

    SERVE:;
    system("clear");
    std::cout << "Launched keybind server. Use ^C to quit." << std::endl;
}
