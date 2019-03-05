cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples.mandelbrot)

find_package(zacc REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(mandelbrot src/mandelbrot.cpp)
add_kernel(mandelbrot_kernel src/kernels.cpp)

target_link_libraries(mandelbrot PRIVATE mandelbrot_kernel host zacc::zacc)

set_target_properties(mandelbrot
        PROPERTIES
        INSTALL_RPATH "@loader_path/../lib "
)

install(TARGETS mandelbrot DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT zacc-examples)

install_kernel(TARGETS mandelbrot_kernel
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT zacc-examples
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT zacc-examples
)