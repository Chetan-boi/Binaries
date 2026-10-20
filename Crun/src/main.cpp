#include "compile.h"
#include "getPathToBinary.h"
#include "runBinary.h"
#include "printHelp.h"
#include "version.h"
#include "colors.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int main(int argc, char* argv[]) {
    std::string buildType;
    bool force = false;
    std::vector<std::string> programArgs;

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg == "--") {
            for (int j = i + 1; j < argc; ++j) {
                programArgs.emplace_back(argv[j]);
            }
            break;
        } else if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        } else if (arg == "-v" || arg == "--version") {
            std::cout << Color::BoldCyan << "Crun " << Color::Reset << "version " << Color::BoldWhite << CRUN_VERSION << Color::Reset << "\n";
            return 0;
        } else if (arg == "-f" || arg == "--force") {
            force = true;
        } else if (arg == "debug" || arg == "release") {
            if (!buildType.empty()) {
                std::cerr << Color::BoldRed << "Error: " << Color::Reset 
                          << "Multiple build types specified ('" << Color::BoldMagenta << buildType << Color::Reset 
                          << "' and '" << Color::BoldMagenta << arg << Color::Reset << "')\n";
                return 1;
            }
            buildType = arg;
        } else {
            std::cerr << Color::BoldRed << "Error: " << Color::Reset << "Unknown option or argument: " << Color::BoldWhite << arg << Color::Reset << "\n";
            std::cerr << "Run '" << Color::BoldGreen << "crun --help" << Color::Reset << "' for usage information.\n";
            return 1;
        }
    }

    int buildStatus = compile(buildType, force);
    if (buildStatus) {
        std::cerr << Color::BoldRed << "Error: " << Color::Reset << "Could not Compile\n";
        return 1;
    }

    std::string pathToBinary = getPathToBinary();
    return runBinary(pathToBinary, programArgs);
}


