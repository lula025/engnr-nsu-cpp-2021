add_executable(main_tests
        mytest.cpp
        )


target_include_directories(main_tests
        PRIVATE "../src/command"
        )
target_link_libraries(main_tests
        command
        gtest
        gmock_main
        )

enable_testing()
add_test(NAME google_test COMMAND main_tests)