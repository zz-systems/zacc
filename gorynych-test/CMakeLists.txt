cmake_minimum_required(VERSION 3.3.2)
project(gorynych-test)

include(../CMakeCommons)

set(BRANCHES_TO_COMPILE
        sse2_branch
        sse3_branch
        ssse3_branch
        sse4_branch
        sse4fma_branch
        avx1_branch
        avx2_branch
		)

set(BRANCH_MODULES
        "float_test\;test_float.cpp"
        "int_test\;test_int.cpp"
        "fastload_int_test\;test_fastload_int.cpp"
        "fastload_float_test\;test_fastload_float.cpp"
		"matrix_test\;test_matrix.cpp"
    )

prepare_branches()

list(APPEND SOURCE_FILES catch_entry_point.cpp)

add_executable(gorynych-test ${SOURCE_FILES})

enable_testing()
add_test(gorynych-test gorynych-test)

add_custom_target(test_gorynych COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS gorynych-test)
