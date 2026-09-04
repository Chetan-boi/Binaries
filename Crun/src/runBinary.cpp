#include "runBinary.h"
#include <filesystem>
#include <string>
#include <iostream>

int runBinary(const std::string& pathToBinary) {
    if (!std::filesystem::exists(pathToBinary)) {
        std::cerr << "Error, the executable does not exist!\n";
        return 1;
    }
    return std::system(pathToBinary.c_str());
}
