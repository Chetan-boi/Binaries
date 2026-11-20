#include "printHelp.hpp"
#include "version.hpp"
#include "colors.hpp"
#include <iostream>

void printHelp() {
    std::cout << Color::BoldCyan << "Crun " << Color::BoldWhite << CRUN_VERSION << Color::Reset 
              << Color::Dim << " — CMake Project Runner\n\n" << Color::Reset
              << "Build and run CMake projects.\n\n"
              << Color::BoldYellow << "USAGE:\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun " << Color::Cyan << "[OPTIONS] [BUILD_TYPE] " << Color::Dim << "[-- PROGRAM_ARGS...]\n"
              << "    " << Color::BoldGreen << "crun " << Color::BoldMagenta << "clean\n\n" << Color::Reset
              << Color::BoldYellow << "BUILD TYPES:\n" << Color::Reset
              << "    " << Color::BoldMagenta << "debug" << Color::Reset << "               Build using the Debug configuration\n"
              << "    " << Color::BoldMagenta << "release" << Color::Reset << "             Build using the Release configuration\n\n"
              << Color::BoldYellow << "OPTIONS:\n" << Color::Reset
              << "    " << Color::BoldGreen << "-f, --force" << Color::Reset << "         Force clean build (removes build directory and re-runs cmake -B build)\n"
              << "    " << Color::BoldGreen << "-q, --quiet" << Color::Reset << "         Hide build output unless the build fails\n"
              << "    " << Color::BoldGreen << "-h, --help" << Color::Reset << "          Print this help message\n"
              << "    " << Color::BoldGreen << "-v, --version" << Color::Reset << "       Print Crun version\n\n"
              << Color::BoldYellow << "COMMANDS:\n" << Color::Reset
              << "    " << Color::BoldMagenta << "clean" << Color::Reset << "               Remove the build directory\n\n"
              << Color::BoldYellow << "PROGRAM ARGUMENTS:\n" << Color::Reset
              << "    Arguments after " << Color::Cyan << "`--`" << Color::Reset << " are passed directly to the executable.\n\n"
              << Color::BoldYellow << "EXAMPLES:\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun " << Color::BoldCyan << "-f\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun " << Color::BoldMagenta << "debug\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun " << Color::BoldCyan << "-f " << Color::BoldMagenta << "debug\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun " << Color::BoldMagenta << "release\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun " << Color::BoldCyan << "-q\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun " << Color::BoldMagenta << "clean\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun " << Color::BoldMagenta << "debug " << Color::Dim << "-- hello world\n" << Color::Reset
              << "    " << Color::BoldGreen << "crun " << Color::BoldMagenta << "release " << Color::Dim << "-- --port 8080\n" << Color::Reset;
}


