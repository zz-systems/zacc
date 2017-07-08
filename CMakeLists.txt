cmake_minimum_required(VERSION 3.6)
project(zacc)

include(cmake/shared.cmake)

#=======================================================================================================================
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(zacc.interface.codegen INTERFACE)
add_dependencies(zacc.interface.codegen "zacc.generate.types.all" "zacc.generate.tests.all" ${target_dependencies})


add_subdirectory(codegen/backend)

include(cmake/dispatched_build.cmake)

# BUILD! ===============================================================================================================

# fetch dependencies
add_subdirectory(dependencies)

# add codegen targets
include(codegen/CMakeLists.txt)

# add app targets
include(src/CMakeLists.txt)

# add test targets
include(test/CMakeLists.txt)

# add documentation targets
include(doc/CMakeLists.txt)