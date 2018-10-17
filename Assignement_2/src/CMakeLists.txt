cmake_minimum_required(VERSION 3.12)
project(INF214)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_executable(Bank1 bank1.cpp)
add_executable(Bank2 bank2.cpp)
add_executable(gcd gcd.cpp)