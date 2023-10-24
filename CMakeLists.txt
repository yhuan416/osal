cmake_minimum_required(VERSION 3.5)

project(osal)

enable_testing()

# 获取posix目录下的所有文件
file(GLOB_RECURSE srcs_posix posix/*.c)

# posix
add_library(osal STATIC ${srcs_posix} osal.c)
target_include_directories(osal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(osal PRIVATE pthread)

add_subdirectory(test)
