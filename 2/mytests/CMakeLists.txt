add_executable(calculator_tests
        mytest.cpp
        )



target_link_libraries(calculator_tests

        gtest
        gmock_main
        )

enable_testing()
add_test(NAME google_test COMMAND calculator_tests)