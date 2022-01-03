cmake_minimum_required(VERSION 3.17)
project(untitled11)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled11 StackCalculator.cpp StackCalculator.h Context.cpp Context.h Parser.cpp Parser.h Commands.cpp Commands.h)