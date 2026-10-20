#include "compile.h"
#include "colors.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

using namespace std::string_literals;

int compile(const std::string& buildType, bool force) {
    if (!std::filesystem::exists("CMakeLists.txt")) {
        std::cerr << Color::BoldRed << "Error: " << Color::Reset << "CMakeLists.txt not found in your current directory\n";
        return 1;
    }

    if (!buildType.empty() && buildType != "debug" && buildType != "release") {
        std::cerr << Color::BoldRed << "Error: " << Color::Reset << "Invalid build type: " << Color::BoldWhite << buildType << Color::Reset << '\n';
        std::cerr << "Expected: " << Color::BoldMagenta << "debug" << Color::Reset << " or " << Color::BoldMagenta << "release" << Color::Reset << '\n';
        return 1;
    }

    if (force && std::filesystem::exists("build")) {
        std::error_code ec;
        std::filesystem::remove_all("build", ec);
        if (ec) {
            std::cerr << Color::BoldRed << "Error: " << Color::Reset << "Failed to remove build directory: " << ec.message() << '\n';
            return 1;
        }
    }

    bool needsConfigure = force || !buildType.empty() || !std::filesystem::exists("build") || !std::filesystem::exists("build/.cmake/api/v1/reply");
    if (needsConfigure) {
        std::error_code ec;
        std::filesystem::create_directories("build/.cmake/api/v1/query", ec);
        std::ofstream queryFile("build/.cmake/api/v1/query/codemodel-v2");
        queryFile.close();

        std::string command = "cmake -B build -DCMAKE_COLOR_DIAGNOSTICS=ON";
        if (!buildType.empty()) {
            command += " -DCMAKE_BUILD_TYPE="s + (buildType == "debug" ? "Debug" : "Release");
        }
        int success = std::system(command.c_str());
        if (success != 0) return 1;
    }

    return std::system("cmake --build build");
}


