cmake_minimum_required(VERSION 3.5.1)
project(atomic_variable)

add_executable(atomic ${PROJECT_NAME}.cpp)
target_link_libraries(atomic pthread)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_CXX_FLAGS "--std=c++17")
set(CMAKE_CXX_COMPILER /usr/bin/g++)
