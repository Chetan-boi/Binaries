#include "runBinary.h"
#include "colors.h"
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

int runBinary(const std::string& pathToBinary, const std::vector<std::string>& args) {
    if (pathToBinary.empty() || !std::filesystem::exists(pathToBinary)) {
        std::cerr << Color::BoldRed << "Error: " << Color::Reset << "The executable does not exist!\n";
        return 1;
    }

    std::string command = pathToBinary.find(' ') != std::string::npos ? "\"" + pathToBinary + "\"" : pathToBinary;
    for (const auto& arg : args) {
        command += " ";
        if (arg.find(' ') != std::string::npos || arg.find('\"') != std::string::npos) {
            command += "\"";
            for (char c : arg) {
                if (c == '\"' || c == '\\') command += '\\';
                command += c;
            }
            command += "\"";
        } else {
            command += arg;
        }
    }

    return std::system(command.c_str());
}

