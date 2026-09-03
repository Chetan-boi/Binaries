#include "runBinary.cpp"
#include <filesystem>

int runBinary(std:;string& pathToBinary) {
    if (!std::filesystem::exists(pathToBinary())) {
        std::cerr << "Error, the executable does not exist!\n"
        return 1;
    }
    return std::system(pathToBinary);

}
