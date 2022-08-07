cmake_minimum_required(VERSION 3.23.0)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "Please create a new directory to save built staffs")
endif()

project(newfeature1 DESCRIPTION "New features of C++, from C++11 to C++20" HOMEPAGE_URL "https://blog.csdn.net/liugan528?type=blog")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(code)
