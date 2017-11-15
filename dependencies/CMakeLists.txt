cmake_minimum_required(VERSION 3.3.2)
project(zacc.dependencies NONE)

add_subdirectory(asyncplusplus)
add_subdirectory(googletest)
include_directories(cimg)