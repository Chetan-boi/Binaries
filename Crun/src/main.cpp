#include "compile.h"
#include "getPathToBinary.h"
#include "runBinary.h"
#include "printHelp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <optional>

int main(int argc, char* argv[]) {
    if (argv[1] == "--help") {
      return printHelp()
      
    }
    std::sting command;
    int buildStatus;
    if (argc > 2) {
        buildStatus = compile(argv[1])
    }
    else {
        buildStatus = compile();
    }
    if (buildStatus) {
        std::cerr << "Could not Compile";
        return 1;
    }

    std::string pathToBinary = getPathToBinary();
    runBinary(pathToBinary);


}
