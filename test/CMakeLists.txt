cmake_minimum_required(VERSION 3.5)

add_executable(main main.c)
target_link_libraries(main osal pthread)

add_test(NAME test COMMAND $<TARGET_FILE:main>)
