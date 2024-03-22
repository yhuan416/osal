cmake_minimum_required(VERSION 3.5)

project(osal C)

# 使能ctest
enable_testing()

# 获取posix目录下的所有文件
# file(GLOB_RECURSE srcs_posix posix/*.c)

# posix
# add_library(osal STATIC ${srcs_posix} osal.c)
# target_include_directories(osal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_link_libraries(osal PRIVATE pthread)

# 获取src目录下的所有文件
file(GLOB_RECURSE srcs_posix src/*.c)
add_library(osal STATIC ${srcs_posix})
target_include_directories(osal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(osal PRIVATE pthread)

# cunit
set(CUNIT_DISABLE_TESTS FALSE)
add_subdirectory(third_party/cunit-3.2.7/CUnit)

# test
add_subdirectory(test)
