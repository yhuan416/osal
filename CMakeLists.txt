cmake_minimum_required(VERSION 3.5)

# 获取src目录下的所有文件
file(GLOB_RECURSE srcs src/*.c)

if (ESP_PLATFORM)

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "src"
                    REQUIRES freertos log)

else ()

project(osal C)

# 使能ctest
enable_testing()

add_library(osal STATIC ${srcs})
target_include_directories(osal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(osal PRIVATE pthread rt)

# cunit
set(CUNIT_DISABLE_TESTS ON)
add_subdirectory(third_party/cunit-3.2.7/CUnit)

# test
add_subdirectory(testsuites)

endif()
