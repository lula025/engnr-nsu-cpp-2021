cmake_minimum_required(VERSION 3.17)
project(Hash_file)

set(CMAKE_CXX_STANDARD 14)
## googletest
#add_subdirectory(lib/googletest)
#include_directories(lib/googletest/googletest/include)
###

add_executable(Hash_file main.cpp Hash_fun.cpp Hash_fun.h)
if (MSVC)
    target_compile_options(Hash_file
            PRIVATE /W4          # warnings level
            PRIVATE /WX          # treat all warnings as errors
            )
else()
    target_compile_options(Hash_file
            PRIVATE -Wall        # basic set of warnings
            PRIVATE -pedantic    # modern C++ inspections
            PRIVATE -Werror      # treat all warnings as errors
            )
endif()