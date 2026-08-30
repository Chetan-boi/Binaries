#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage : Cnew <projectName>";
    return 1;
  }
  std::string projectName = argv[1];
  std::filesystem::create_directories(projectName + "/src");
  std::filesystem::create_directories(projectName + "/include");
  std::ofstream CmakeText(projectName + "/CMakeLists.txt");
  if (!CmakeText) {
    std::cerr << "Failed to create CmakeLists.txt";
    return 1;
  }
  CmakeText << "cmake_minimum_required(VERSION 3.10)\n"
            << "project(" << projectName << " LANGUAGES CXX)\n\n"
            << "set(CMAKE_CXX_STANDARD 20)\n"
            << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n"
            << "add_executable(" << projectName << " src/main.cpp)\n";

  CmakeText.close();

  std::ofstream main(projectName + "/src/main.cpp");
  if (!main) {
    std::cerr << "Failed to create main.cpp";
    return 1;
  }
  main << "#include <iostream>\n\n"
       << "int main() {\n"
       << "\tstd::cout << \"Hello World!\";\n"
       << "\treturn 0;\n}";
  std::cout << projectName << " Created successfully";
  return 0;
}
