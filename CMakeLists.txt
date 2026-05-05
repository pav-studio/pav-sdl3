cmake_minimum_required(VERSION 3.16)
project(RoguePong)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL3 REQUIRED)

add_executable(RoguePong src/main.cpp)

target_link_libraries(RoguePong SDL3::SDL3)