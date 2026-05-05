cmake_minimum_required(VERSION 3.16)
project(PingPong)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL3 REQUIRED)

add_executable(PingPong src/main.cpp)

target_link_libraries(PingPong SDL3::SDL3)