cmake_minimum_required(VERSION 3.3.2)
project(zacc.test NONE)

enable_testing()

find_package(zacc REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB test.algorithm    "src/algorithm/*.cpp")
file(GLOB test.core         "src/cast.cpp")
file(GLOB test.traits       "src/traits/*.cpp")
file(GLOB test.math         "src/math/*.cpp")
file(GLOB_RECURSE test.util "src/util/*.cpp")

#
#if(BUILD_SANITIZE_MEMORY)
#    add_compile_options(-fsanitize=address)
#    link_libraries(-fsanitize=address)
#endif()


add_custom_target(zacc_test)
set(test_categories traits math util algorithm)

foreach(category ${test_categories})
    set(test_name zacc_test_${category})
    set(kernel_name zacc_test_${category}_kernel)

    add_executable(${test_name} src/test_host.cpp)
    add_kernel(${kernel_name} src/kernels.cpp ${test.${category}} NOLINK)

    target_link_libraries(${test_name} PRIVATE ${kernel_name})
    kernel_link_libraries(${kernel_name} PRIVATE gtest)

    add_permuted_tests(${test_name})

    add_dependencies(zacc_test ${test_name})
endforeach()