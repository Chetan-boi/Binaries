#include "runBinary.hpp"
#include "colors.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <sys/wait.h>

std::string shellQuote(const std::string& s) {
    std::string out = "'";
    for (char c : s) {
        if (c == '\'') out += "'\\''";
        else out += c;
    }
    return out + "'";
}

int runBinary(const std::string& pathToBinary, const std::vector<std::string>& args) {
    if (pathToBinary.empty() || !std::filesystem::exists(pathToBinary)) {
        std::cerr << Color::BoldRed << "Error: " << Color::Reset << "The executable does not exist!\n";
        return 1;
    }

    std::string command = shellQuote(pathToBinary);
    for (const auto& arg : args) {
        command += " " + shellQuote(arg);
    }

    int status = std::system(command.c_str());
    if (status == -1) return 1;
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) return 128 + WTERMSIG(status);
    return 1;
}
