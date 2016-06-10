cmake_minimum_required(VERSION 3.3.2)
project(gorynych-test)

include(../CMakeCommons)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3")

#set(CMAKE_BUILD_TYPE Debug)
set( CMAKE_VERBOSE_MAKEFILE on )
set(CMAKE_CXX_FLAGS "-std=c++14 -O3 -march=x86-64")


set(BRANCHES_TO_COMPILE
        sse2_branch
        sse3_branch
        ssse3_branch
        sse4_branch
        sse4fma_branch
        avx1_branch
        avx2_branch)

set(BRANCH_MODULES
        "float_test\;test_float.cpp"
        "int_test\;test_int.cpp"
        "fastload_int_test\;test_fastload_int.cpp"
        "fastload_float_test\;test_fastload_float.cpp"
    )

prepare_branches()

list(APPEND SOURCE_FILES catch_entry_point.cpp)

add_executable(gorynych-test ${SOURCE_FILES})

enable_testing()
add_test(gorynych-test gorynych-test)

add_custom_target(unit_test COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS gorynych-test)