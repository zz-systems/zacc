cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples.julia)

find_package(zacc REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(julia src/julia.cpp)
add_kernel(julia_kernel src/kernels.cpp)

target_link_libraries(julia PRIVATE julia_kernel host zacc::zacc)

set_target_properties(julia
    PROPERTIES
    INSTALL_RPATH "@loader_path/../lib "
)

install(TARGETS julia DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT zacc-examples)

install_kernel(TARGETS julia_kernel
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT zacc-examples
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT zacc-examples
)