cmake_minimum_required(VERSION 3.10)
project(test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(test src/main.cpp)
target_include_directories(test PRIVATE include)
