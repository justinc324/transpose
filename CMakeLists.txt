cmake_minimum_required(VERSION 3.8)
project(transpose)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES transpose.c)
add_executable(transpose ${SOURCE_FILES})