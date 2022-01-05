add_executable(main
        main.cpp
        )

target_include_directories(main
        PRIVATE "../command"
        )

target_link_libraries(main
        command
        )