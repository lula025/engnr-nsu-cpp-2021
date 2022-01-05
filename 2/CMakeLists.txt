cmake_minimum_required(VERSION 3.17)
project(2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
add_subdirectory(SafeInt)
include_directories(SafeInt)

add_subdirectory(src/main)
add_subdirectory(src/command)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(mytests)
if (MSVC)
    target_compile_options(main
            PRIVATE /W4
            #            PRIVATE /WX
            )
else()
    target_compile_options(main
            PRIVATE -Wall
            PRIVATE -pedantic
            )
endif()

