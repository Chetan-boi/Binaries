cmake_minimum_required(VERSION 3.14)
project(Crun VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(Crun ${SOURCES})
target_include_directories(Crun PRIVATE include)
target_compile_definitions(Crun PRIVATE CRUN_VERSION="${PROJECT_VERSION}")

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(Crun PRIVATE nlohmann_json::nlohmann_json)
