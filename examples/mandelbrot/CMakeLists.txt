cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples.mandelbrot)

include_directories("${PROJECT_SOURCE_DIR}/include")

zacc_add_dispatched_executable(zacc.examples.mandelbrot
        BRANCHES "${branches}"
        KERNELS
        ${PROJECT_SOURCE_DIR}/src/kernels.cpp
        SOURCES
        ${PROJECT_SOURCE_DIR}/src/mandelbrot.cpp
        )

if(NOT WIN32)
    find_package(X11 REQUIRED)

    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

    include_directories(${X11_INCLUDE_DIR})

    link_directories(${X11_LIBRARIES})

    target_link_libraries(zacc.examples.mandelbrot PRIVATE ${X11_LIBRARIES})

    link_directories("/usr/X11/lib" "/usr/X11R6/lib")

    if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        target_link_libraries(zacc.examples.mandelbrot PRIVATE jpeg png m pthread)
    endif()
endif()