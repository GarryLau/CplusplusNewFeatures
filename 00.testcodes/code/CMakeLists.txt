cmake_minimum_required(VERSION 3.23.0)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "Please create a new directory to save built staffs")
endif()

if(USE_32BITS)
 message(STATUS "using 32bits")
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
 
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
 
else()
endif(USE_32BITS)

aux_source_directory(. SOURCE_FILES)
message(STATUS "------>${SOURCE_FILES}<--------")
add_executable(runNewFeat ${SOURCE_FILES})
