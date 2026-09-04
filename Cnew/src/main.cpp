#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace Color {
inline constexpr const char *RESET = "\033[0m";
inline constexpr const char *BOLD = "\033[1m";
inline constexpr const char *DIM = "\033[2m";
inline constexpr const char *RED = "\033[31m";
inline constexpr const char *GREEN = "\033[32m";
inline constexpr const char *YELLOW = "\033[33m";
inline constexpr const char *BLUE = "\033[34m";
inline constexpr const char *MAGENTA = "\033[35m";
inline constexpr const char *CYAN = "\033[36m";
inline constexpr const char *WHITE = "\033[37m";
inline constexpr const char *BRIGHT_RED = "\033[91m";
inline constexpr const char *BRIGHT_GREEN = "\033[92m";
inline constexpr const char *BRIGHT_YELLOW = "\033[93m";
inline constexpr const char *BRIGHT_CYAN = "\033[96m";
} // namespace Color

void printHelp() {
  std::cout << Color::BOLD << Color::BRIGHT_CYAN << "Cnew" << Color::RESET
            << " - " << Color::DIM << "Modern C++ Project Generator"
            << Color::RESET << "\n\n"
            << Color::BOLD << Color::BRIGHT_YELLOW << "Usage:" << Color::RESET
            << "\n"
            << "  " << Color::CYAN << "Cnew" << Color::RESET << " "
            << Color::GREEN << "<projectName>" << Color::RESET << "\n"
            << "  " << Color::CYAN << "Cnew" << Color::RESET << " "
            << Color::WHITE << "--help" << Color::RESET << " | " << Color::WHITE
            << "-h" << Color::RESET << "\n"
            << "  " << Color::CYAN << "Cnew" << Color::RESET << " "
            << Color::WHITE << "--version" << Color::RESET << " | "
            << Color::WHITE << "-v" << Color::RESET << "\n\n"
            << Color::BOLD << Color::BRIGHT_YELLOW
            << "Description:" << Color::RESET << "\n"
            << "  Scaffolds a modern C++20 project with a standard directory "
               "structure,\n"
            << "  pre-configured CMakeLists.txt, and CMake File API query "
               "support.\n\n"
            << Color::BOLD << Color::BRIGHT_YELLOW << "Options:" << Color::RESET
            << "\n"
            << "  " << Color::BRIGHT_CYAN << "-h, --help" << Color::RESET
            << "       Display this help message\n"
            << "  " << Color::BRIGHT_CYAN << "-v, --version" << Color::RESET
            << "    Display version information\n\n"
            << Color::BOLD << Color::BRIGHT_YELLOW << "Example:" << Color::RESET
            << "\n"
            << "  " << Color::CYAN << "Cnew " << Color::GREEN << "MyAwesomeApp"
            << Color::RESET << "\n";
}

void printVersion() {
  std::cout << Color::BOLD << Color::BRIGHT_CYAN << "Cnew" << Color::RESET
            << " version " << Color::BRIGHT_GREEN << "1.0.0" << Color::RESET
            << "\n";
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << Color::BOLD << Color::BRIGHT_RED
              << "[!] Error: " << Color::RESET << "Missing project name.\n\n";
    printHelp();
    return 1;
  }

  std::string firstArg = argv[1];

  if (firstArg == "--help" || firstArg == "-h" || firstArg == "help") {
    printHelp();
    return 0;
  }

  if (firstArg == "--version" || firstArg == "-v") {
    printVersion();
    return 0;
  }

  if (firstArg.rfind("-", 0) == 0) {
    std::cerr << Color::BOLD << Color::BRIGHT_RED
              << "[!] Error: " << Color::RESET << "Unknown option '" << firstArg
              << "'. Use --help for usage.\n";
    return 1;
  }

  std::string projectName = firstArg;
  std::error_code ec;

  std::cout << Color::BOLD << Color::BRIGHT_CYAN
            << "[*] Initializing new C++ project: " << Color::BRIGHT_GREEN
            << "'" << projectName << "'" << Color::RESET << "\n\n";

  // 1. Create directories
  std::cout << Color::BOLD << Color::BLUE << "[+] " << Color::RESET
            << "Creating directory structure...\n";

  fs::path projectPath = projectName;
  fs::path srcPath = projectPath / "src";
  fs::path includePath = projectPath / "include";
  fs::path cmakeQueryPath =
      projectPath / "build" / ".cmake" / "api" / "v1" / "query";

  fs::create_directories(srcPath, ec);
  if (ec) {
    std::cerr << Color::BOLD << Color::BRIGHT_RED
              << "[!] Error creating directory '" << srcPath.string()
              << "': " << Color::RESET << ec.message() << "\n";
    return 1;
  }

  fs::create_directories(includePath, ec);
  if (ec) {
    std::cerr << Color::BOLD << Color::BRIGHT_RED
              << "[!] Error creating directory '" << includePath.string()
              << "': " << Color::RESET << ec.message() << "\n";
    return 1;
  }

  // 2. Create CMakeLists.txt
  std::cout << Color::BOLD << Color::BLUE << "[+] " << Color::RESET
            << "Generating CMakeLists.txt...\n";
  fs::path cmakeListsPath = projectPath / "CMakeLists.txt";
  std::ofstream cmakeFile(cmakeListsPath);
  if (!cmakeFile) {
    std::cerr << Color::BOLD << Color::BRIGHT_RED
              << "[!] Error: Failed to create " << cmakeListsPath.string()
              << Color::RESET << "\n";
    return 1;
  }
  cmakeFile << "cmake_minimum_required(VERSION 3.10)\n"
            << "project(" << projectName << " LANGUAGES CXX)\n\n"
            << "set(CMAKE_CXX_STANDARD 20)\n"
            << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n"
            << "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n"
            << "add_executable(" << projectName << " src/main.cpp)\n"
            << "target_include_directories(" << projectName
            << " PRIVATE include)\n";
  cmakeFile.close();

  // 3. Setup CMake File API query
  std::cout << Color::BOLD << Color::BLUE << "[+] " << Color::RESET
            << "Setting up CMake File API query...\n";
  fs::create_directories(cmakeQueryPath, ec);
  if (ec) {
    std::cerr << Color::BOLD << Color::BRIGHT_RED
              << "[!] Error creating directory '" << cmakeQueryPath.string()
              << "': " << Color::RESET << ec.message() << "\n";
    return 1;
  }

  fs::path codeModelPath = cmakeQueryPath / "codemodel-v2";
  std::ofstream codeModelFile(codeModelPath);
  if (!codeModelFile) {
    std::cerr << Color::BOLD << Color::BRIGHT_RED
              << "[!] Error: Failed to create " << codeModelPath.string()
              << Color::RESET << "\n";
    return 1;
  }
  codeModelFile.close();

  // 4. Generate starter main.cpp
  std::cout << Color::BOLD << Color::BLUE << "[+] " << Color::RESET
            << "Generating starter source file...\n";
  fs::path mainFilePath = srcPath / "main.cpp";
  std::ofstream mainFile(mainFilePath);
  if (!mainFile) {
    std::cerr << Color::BOLD << Color::BRIGHT_RED
              << "[!] Error: Failed to create " << mainFilePath.string()
              << Color::RESET << "\n";
    return 1;
  }
  mainFile << "#include <iostream>\n\n"
           << "int main() {\n"
           << "    std::cout << \"Hello World!\\n\";\n"
           << "    return 0;\n"
           << "}\n";
  mainFile.close();

  std::cout << "\n"
            << Color::BOLD << Color::BRIGHT_GREEN << "[✓] Project '"
            << projectName << "' created successfully!" << Color::RESET << "\n";

  return 0;
}
