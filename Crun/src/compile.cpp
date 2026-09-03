#include "compile.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std::string_literals;

static void ensureCMakeApiQuery() {
    std::filesystem::path queryDir = "build/.cmake/api/v1/query";
    std::error_code ec;
    std::filesystem::create_directories(queryDir, ec);
    if (!ec) {
        std::ofstream queryFile(queryDir / "codemodel-v2");
    }
}

int compile(const std::string& buildType) {
    if (!std::filesystem::exists("CMakeLists.txt")) {
        std::cerr << "\033[1;31m[Crun Error]\033[0m CMakeLists.txt was not found in the current working directory ('"
                  << std::filesystem::current_path().string() << "').\n"
                  << "\033[1;33m[Hint]\033[0m Make sure you run crun from the root directory of your CMake project.\n";
        return 1;
    }

    ensureCMakeApiQuery();

    bool needsConfig = !std::filesystem::exists("build/CMakeCache.txt") ||
                       !std::filesystem::exists("build/.cmake/api/v1/reply");

    if (!buildType.empty()) {
        if (buildType != "debug" && buildType != "release") {
            std::cerr << "\033[1;31m[Crun Error]\033[0m Invalid build type: '" << buildType << "'.\n"
                      << "\033[1;33m[Hint]\033[0m Supported build types are '\033[1;36mdebug\033[0m' or '\033[1;36mrelease\033[0m'.\n";
            return 1;
        }
        std::string cmakeType = (buildType == "debug" ? "Debug" : "Release");
        std::string command = "cmake -B build -DCMAKE_BUILD_TYPE="s + cmakeType;
        int status = std::system(command.c_str());
        if (status != 0) {
            std::cerr << "\033[1;31m[Crun Error]\033[0m CMake configuration failed with exit code " << status << ".\n";
            return status;
        }
    } else if (needsConfig) {
        int status = std::system("cmake -B build");
        if (status != 0) {
            std::cerr << "\033[1;31m[Crun Error]\033[0m CMake configuration failed with exit code " << status << ".\n";
            return status;
        }
    }

    int buildStatus = std::system("cmake --build build");
    if (buildStatus != 0) {
        std::cerr << "\033[1;31m[Crun Error]\033[0m CMake build failed with exit code " << buildStatus << ".\n";
        return buildStatus;
    }
    return 0;
}

