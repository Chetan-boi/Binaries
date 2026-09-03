# Enforce the minimum CMake version required to parse this file
cmake_minimum_required(VERSION 3.10)
project(Crun LANGUAGES CXX)

# Specify the C++ standard (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate a compile_commands.json database (used by clangd, LSP, and tooling)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all .cpp source files from the src directory
# Note: CONFIGURE_DEPENDS can be added so CMake detects added/removed files automatically
file(GLOB SOURCES "src/*.cpp")
add_executable(Crun ${SOURCES})

# Add the 'include' directory to the compiler's header search path for this target only
target_include_directories(Crun PRIVATE include)
