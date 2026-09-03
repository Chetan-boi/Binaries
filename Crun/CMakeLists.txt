# Enforce minimum CMake 3.14
cmake_minimum_required(VERSION 3.14)

# Define the project name and set the language to C++
project(Crun LANGUAGES CXX)

# Enforce the C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile_commands.json for clangd and Neovim LSP support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Automatically gather all .cpp source files in the src/ directory
# CONFIGURE_DEPENDS ensures CMake re-runs automatically when files are added or deleted
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Create the binary executable from the gathered sources
add_executable(Crun ${SOURCES})

# Expose the include/ directory to your source files for #include lookups
target_include_directories(Crun PRIVATE include)

# Download and link nlohmann/json directly via Git
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

# Link the JSON library to your Crun executable
target_link_libraries(Crun PRIVATE nlohmann_json::nlohmann_json)
