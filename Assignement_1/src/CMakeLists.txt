cmake_minimum_required(VERSION 3.12)
project(INF214)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_executable(lockingQueue locking_queue.cpp)
add_executable(atomicQueue atomic_queue.cpp)