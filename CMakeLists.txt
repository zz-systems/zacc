cmake_minimum_required(VERSION 3.6)
project(zacc)

include(cmake/zacc.shared.cmake)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# include branched code generation config
add_subdirectory(codegen/backend)

# fetch dependencies
add_subdirectory(dependencies)

# add codegen targets
include(codegen/CMakeLists.txt)

# add app targets
include(src/CMakeLists.txt)

# add test targets
add_subdirectory(test)

# add documentation targets
include(doc/CMakeLists.txt)