cmake_minimum_required(VERSION 3.17)
project(2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(2 Commands.h Commands.cpp main.cpp StackCalculator.h StackCalculator.cpp mytests/mytest.cpp)
add_subdirectory(googletest)

# For Windows: Prevent overriding the parent project's compiler/linker settings

