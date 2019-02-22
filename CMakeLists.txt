cmake_minimum_required(VERSION 3.3.2)
project(zacc)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/zacc.shared.cmake)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_DOCS "Build documentation" ON)

# include branched code generation config
add_subdirectory(codegen/backend)

# fetch dependencies
if(BUILD_EXAMPLES OR BUILD_TESTS)
    add_subdirectory(dependencies)
endif()

# add codegen targets
include(codegen/CMakeLists.txt)

# add app targets
include(src/CMakeLists.txt)

# add test targets
if(BUILD_TESTS)
    enable_testing()
    include(test/CMakeLists.txt)
endif()

# add example targets
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# add documentation targets
if(BUILD_DOCS)
    include(docs/CMakeLists.txt)
endif()