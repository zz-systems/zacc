cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples.mandelbrot)

find_package(zacc REQUIRED)

set(include_directories
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
)

add_executable(mandelbrot src/mandelbrot.cpp)
target_include_directories(mandelbrot PUBLIC
        ${include_directories}
)

add_kernel(mandelbrot_kernel src/kernels.cpp)
kernel_include_directories(mandelbrot_kernel PUBLIC
        ${include_directories}
)

target_link_libraries(mandelbrot PRIVATE host mandelbrot_kernel zacc::zacc)

set_target_properties(mandelbrot
        PROPERTIES
        INSTALL_RPATH "@loader_path/../lib "
)

install(TARGETS mandelbrot DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT zacc-examples)

install_kernel(TARGETS mandelbrot_kernel
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT zacc-examples
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT zacc-examples
)

if(NOT WIN32)
    find_package(X11 REQUIRED)

    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

    include_directories(${X11_INCLUDE_DIR})

    link_directories(${X11_LIBRARIES})

    target_link_libraries(mandelbrot PRIVATE ${X11_LIBRARIES})

    link_directories("/usr/X11/lib" "/usr/X11R6/lib")

    if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        target_link_libraries(mandelbrot PRIVATE jpeg png m pthread)
    endif()
endif()