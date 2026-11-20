#include "compile.hpp"
#include "colors.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

namespace fs = std::filesystem;

static void printError(const std::string& message) {
    std::cerr << Color::BoldRed << "Error: " << Color::Reset << message << '\n';
}

// Runs a command. In quiet mode its output goes to a log file that is only
// shown if the command fails.
static int runStep(const std::string& command, bool quiet) {
    if (!quiet) return std::system(command.c_str());

    fs::path log = fs::temp_directory_path() / ("crun-" + std::to_string(getpid()) + ".log");
    int status = std::system((command + " > '" + log.string() + "' 2>&1").c_str());

    if (status != 0) {
        std::ifstream file(log);
        std::stringstream contents;
        contents << file.rdbuf();
        std::cerr << contents.str();
    }
    std::error_code ec;
    fs::remove(log, ec);
    return status;
}

int clean() {
    if (!fs::exists("build")) {
        std::cout << "Nothing to clean\n";
        return 0;
    }
    std::error_code ec;
    fs::remove_all("build", ec);
    if (ec) {
        printError("Failed to remove build directory: " + ec.message());
        return 1;
    }
    std::cout << Color::BoldGreen << "Cleaned " << Color::Reset << "build/\n";
    return 0;
}

int compile(const std::string& buildType, bool force, bool quiet) {
    if (!fs::exists("CMakeLists.txt")) {
        printError("CMakeLists.txt not found in your current directory");
        return 1;
    }

    if (!buildType.empty() && buildType != "debug" && buildType != "release") {
        printError("Invalid build type: " + std::string(Color::BoldWhite) + buildType + Color::Reset);
        std::cerr << "Expected: " << Color::BoldMagenta << "debug" << Color::Reset << " or "
                  << Color::BoldMagenta << "release" << Color::Reset << '\n';
        return 1;
    }

    if (force && fs::exists("build")) {
        std::error_code ec;
        fs::remove_all("build", ec);
        if (ec) {
            printError("Failed to remove build directory: " + ec.message());
            return 1;
        }
    }

    bool needsConfigure = force || !buildType.empty() || !fs::exists("build") ||
                          !fs::exists("build/.cmake/api/v1/reply");
    if (needsConfigure) {
        std::error_code ec;
        fs::create_directories("build/.cmake/api/v1/query", ec);
        std::ofstream("build/.cmake/api/v1/query/codemodel-v2");

        std::string command = "cmake -B build -DCMAKE_COLOR_DIAGNOSTICS=ON";
        if (!buildType.empty()) {
            command += std::string(" -DCMAKE_BUILD_TYPE=") + (buildType == "debug" ? "Debug" : "Release");
        }
        if (runStep(command, quiet) != 0) return 1;
    }

    return runStep("cmake --build build", quiet);
}
