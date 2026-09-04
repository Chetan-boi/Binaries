#include "compile.h"
#include <filesystem>
#include <string>
#include <iostream>

using namespace std::string_literals;

int compile(const std::string& buildType) {
    if (!buildType.empty()) {
        if (!std::filesystem::exists("CMakeLists.txt")) {
            std::cerr << "CMakeLists.txt not found in your current directory";
            return 1;
        }
        if (buildType != "debug" && buildType != "release") {
            std::cerr << "Invalid build type: " << buildType << '\n';
            std::cerr << "Expected: debug or release\n";
            return 1;
        }
        std::string command = "cmake -B build -DCMAKE_BUILD_TYPE="s + (buildType == "debug" ? "Debug" : "Release");
        int success = std::system(command.c_str());
        if (success) return 1;
    }
    return std::system("cmake --build build");
}
