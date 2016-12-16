cmake_minimum_required(VERSION 3.6)
project(zacc)

set(CMAKE_CXX_STANDARD 14)

add_executable(zacc ${SOURCE_FILES} tests/test.cpp)

target_compile_options(zacc PUBLIC -msse2 -msse3 -mssse3 -msse4)