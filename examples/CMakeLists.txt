cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples)

find_package(ZACC REQUIRED)

add_library(host INTERFACE)
target_include_directories(host INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(host INTERFACE cimg)

add_subdirectory(julia)
add_subdirectory(mandelbrot)