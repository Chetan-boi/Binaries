#include "printHelp.h"
#include <iostream>

void printHelp() {
 std::cout << R"(Crun — CMake Project Runner

Build and run CMake projects.

USAGE:
    crun [BUILD_TYPE] [-- PROGRAM_ARGS...]

BUILD TYPES:
    debug               Build using the Debug configuration
    release             Build using the Release configuration

OPTIONS:
    -h, --help          Print this help message
    -v, --version       Print Crun version

PROGRAM ARGUMENTS:
    Arguments after `--` are passed directly to the executable.

EXAMPLES:
    crun
    crun debug
    crun release
    crun debug -- hello world
    crun release -- --port 8080
)"; 
}
