#include "compile.h"
#include "getPathToBinary.h"
#include "runBinary.h"
#include "printHelp.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int main(int argc, char* argv[]) {
    std::string buildType = "";
    std::vector<std::string> programArgs;

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        }
        if (arg == "-v" || arg == "--version") {
            std::cout << "\033[1;36mCrun\033[0m version \033[1;32m0.1.0\033[0m\n";
            return 0;
        }
        if (arg == "--") {
            for (int j = i + 1; j < argc; ++j) {
                programArgs.emplace_back(argv[j]);
            }
            break;
        }
        if (arg == "debug" || arg == "release") {
            buildType = arg;
        } else {
            std::cerr << "\033[1;31m[Crun Error]\033[0m Unknown option or argument: '" << arg << "'\n"
                      << "\033[1;33m[Hint]\033[0m Run '\033[1;36mcrun --help\033[0m' for usage details.\n";
            return 1;
        }
    }

    int buildStatus = compile(buildType);
    if (buildStatus != 0) {
        std::cerr << "\033[1;31m[Crun Error]\033[0m Build step failed with status " << buildStatus << ". Execution aborted.\n";
        return buildStatus;
    }

    std::string pathToBinary = getPathToBinary();
    if (pathToBinary.empty()) {
        std::cerr << "\033[1;31m[Crun Error]\033[0m Could not locate built binary. Execution aborted.\n";
        return 1;
    }

    return runBinary(pathToBinary, programArgs);
}
