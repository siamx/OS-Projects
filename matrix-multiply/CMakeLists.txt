cmake_minimum_required(VERSION 3.8)
project(matrix_multiply)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES main.c Matrix_Ops.c Matrix_Ops.h)

add_executable(matrix_multiply ${SOURCE_FILES})
