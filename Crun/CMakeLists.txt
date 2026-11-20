cmake_minimum_required(VERSION 3.14)
project(Crun VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(Crun ${SOURCES})
target_include_directories(Crun PRIVATE include)
target_compile_definitions(Crun PRIVATE CRUN_VERSION="${PROJECT_VERSION}")
target_link_libraries(Crun PRIVATE nlohmann_json::nlohmann_json)

# Tests
include(CTest)

# doctest's own CMakeLists declares a very old minimum version
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_Declare(
    doctest
    URL https://github.com/doctest/doctest/archive/refs/tags/v2.4.11.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(doctest)

add_executable(CrunTests tests/test_main.cpp src/runBinary.cpp)
target_include_directories(CrunTests PRIVATE include)
target_link_libraries(CrunTests PRIVATE doctest::doctest)
add_test(NAME CrunTests COMMAND CrunTests)
