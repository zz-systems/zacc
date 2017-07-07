cmake_minimum_required(VERSION 3.6)
project(zacc)

include(cmake/shared.cmake)
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