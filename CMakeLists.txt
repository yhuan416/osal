cmake_minimum_required(VERSION 3.5)

project(osal)

# 获取posix目录下的所有文件
file(GLOB_RECURSE srcs_posix posix/*.c)

# posix
add_library(osal STATIC ${srcs_posix})
target_include_directories(osal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(osal PRIVATE pthread)
