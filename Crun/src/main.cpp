#include "compile.h"
#include "getPathToBinary.h"
#include "runBinary.h"
#include "printHelp.h"
#include <iostream>
// #include <fstream>
// #include <filesystem>
#include <string>
#include <string_view>
// #include <optional>

int main(int argc, char* argv[]) {
  int buildStatus;
  if (argc <= 2) {
    buildStatus = compile();
  }
  else if (std::string_view(argv[1]) == "--help") {
    printHelp();
    return 0;
  }
  std::string command;
  if (argc > 2) {
      buildStatus = compile(argv[1]);
  }
  if (buildStatus) {
      std::cerr << "Could not Compile";
      return 1;
  }
  std::string pathToBinary = getPathToBinary();
  return runBinary(pathToBinary);
}
