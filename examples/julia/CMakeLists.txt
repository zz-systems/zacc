cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples.mandelbrot)

include_directories("${PROJECT_SOURCE_DIR}/include")

zacc_add_dispatched_executable(zacc.examples.julia
        BRANCHES "${branches}"
        KERNELS
            ${PROJECT_SOURCE_DIR}/src/kernels.cpp
        SOURCES
            ${PROJECT_SOURCE_DIR}/src/julia.cpp
        )


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # requires XQuartz
    target_include_directories(zacc.examples.julia PRIVATE "/usr/X11/include")
    link_directories("/usr/X11/lib" "/usr/X11R6/lib")
    target_link_libraries(zacc.examples.julia PRIVATE X11)
elseif(NOT WIN32)
    target_link_libraries(zacc.examples.julia PRIVATE X11 jpeg png m pthread)
endif()