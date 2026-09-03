#include "runBinary.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int runBinary(const std::string& pathToBinary, const std::vector<std::string>& args) {
    if (pathToBinary.empty()) {
        return 1;
    }
    if (!std::filesystem::exists(pathToBinary)) {
        std::cerr << "\033[1;31m[Crun Error]\033[0m Executable binary not found at: '"
                  << pathToBinary << "'\n"
                  << "\033[1;33m[Hint]\033[0m Verify that CMake built the target successfully.\n";
        return 1;
    }

    std::string command = "\"" + pathToBinary + "\"";
    for (const auto& arg : args) {
        command += " \"" + arg + "\"";
    }

    return std::system(command.c_str());
}
