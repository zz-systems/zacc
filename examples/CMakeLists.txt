cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(julia)
add_subdirectory(mandelbrot)