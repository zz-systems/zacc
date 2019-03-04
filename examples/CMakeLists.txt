cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples)

find_package(ZACC REQUIRED)

add_library(host INTERFACE)
target_include_directories(host INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>)

add_subdirectory(julia)
add_subdirectory(mandelbrot)