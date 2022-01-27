cmake_minimum_required(VERSION 3.17)
project(3)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(googletest)

enable_testing()

add_executable(3 main.cpp linked_list.h)
add_executable(linked_list_tests tests.cpp)
if (WIN32)
    #do something
else()
    target_compile_options(linked_list_tests PUBLIC
            -fno-omit-frame-pointer -fsanitize=address)
    target_link_options(linked_list_tests PUBLIC
            -fno-omit-frame-pointer -fsanitize=address)
endif()

target_link_libraries(linked_list_tests
        gtest
        gmock_main
        )

add_test(NAME googletest COMMAND linked_list_tests)