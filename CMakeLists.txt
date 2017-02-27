cmake_minimum_required(VERSION 3.6)
project(zacc)

set(CMAKE_CXX_STANDARD 14)

# Clang doesn't support the __float128 type. Here are some workarounds:
# https://bugs.llvm.org//show_bug.cgi?id=13530#c3
# 1) build with -D__STRICT_ANSI__
# 2) edit bits/c++config.h (somewhere inside /usr/include/c++/4.7.0) so it doesn't define _GLIBCXX_USE_FLOAT128
# 3) configure libstdc++ with clang instead of gcc
# 4) add 'struct __float128;' before you include any STL header
add_definitions(-D__STRICT_ANSI__)

include_directories(
        ${CMAKE_SOURCE_DIR}/zacc
        ${CMAKE_SOURCE_DIR})

include(${CMAKE_SOURCE_DIR}/tests/tests.cmake)
include(${CMAKE_SOURCE_DIR}/auxapps/auxapps.cmake)

set(template.schema ".hpp.yml")
set(impl.schema ".impl.hpp")
set(test.schema ".test.cpp")

set(type_template "common/templates/type.impl.jinja")
set(test_template "common/templates/type.test.jinja")

set(yasha.cmd "C:/Python/Scripts/yasha")
set(yasha.deps
        "common/templates/type.py"
        "common/templates/type.test.yml"
        ${type_template}
        ${test_template}
        )


option(BUILD_SCALAR_BRANCH "Build the scalar branch" ON)
option(BUILD_SSE_BRANCH "Build the sse branch" ON)
option(BUILD_AVX_BRANCH "Build the avx branch" ON)
option(BUILD_AVX2_BRANCH "Build the avx2 branch" ON)
option(BUILD_AVX512_BRANCH "Build the avx512 branch" OFF)

macro(add_compiler_flag key)
    set("compiler_flags_${key}" ${ARGN})
endmacro()

macro(add_branch_def key)
    set("branch_defs_${key}" ${ARGN})
endmacro()

add_compiler_flag(scalar    "")
add_compiler_flag(sse       -msse2)
add_compiler_flag(sse_3     -msse3 -mssse3)
add_compiler_flag(sse_4     -msse4.1 -msse4.2)
add_compiler_flag(sse_4fma  -msse4.1 -msse4.2 -mfma)
add_compiler_flag(avx       -mavx)
add_compiler_flag(avx2      -mavx2)
add_compiler_flag(avx512    -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)

add_branch_def(scalar   ZACC_SCALAR)
add_branch_def(sse      ZACC_SSE2)
add_branch_def(sse_3    ZACC_SSE2 ZACC_SSE3)
add_branch_def(sse_4    ZACC_SSE2 ZACC_SSE3 ZACC_SSE4)
add_branch_def(sse_4fma ZACC_SSE2 ZACC_SSE3 ZACC_SSE4 ZACC_SSE4FMA)
add_branch_def(avx      ZACC_AVX)
add_branch_def(avx2     ZACC_AVX2)
add_branch_def(avx512   ZACC_AVX2)

if(BUILD_SCALAR_BRANCH)
    list(APPEND branches scalar)
endif()

if(BUILD_SSE_BRANCH)
    list(APPEND branches sse)
    list(APPEND branches sse_3)
    list(APPEND branches sse_4)
    list(APPEND branches sse_4fma)
endif()

if(BUILD_AVX_BRANCH)
    list(APPEND branches avx)
endif()

if(BUILD_AVX2_BRANCH)
    list(APPEND branches avx2)
endif()

if(BUILD_AVX512_BRANCH)
    list(APPEND branches avx512)
endif()

function(get_sources branch_files branch_name)
    file(GLOB_RECURSE branch_test ABSOLUTE ${CMAKE_SOURCE_DIR}    "*/${branch_name}/*${impl.schema}")
    file(GLOB_RECURSE branch_impl ABSOLUTE ${CMAKE_SOURCE_DIR}    "*/${branch_name}/*${test.schema}")

    set(branch_files ${branch_test} ${branch_impl} PARENT_SCOPE)
endfunction()

function(preprocess_paths path type template)
    string(REGEX REPLACE "${template.schema}" "${${type}.schema}" outpath ${template})
    string(REPLACE "config/" "${type}/" outpath ${outpath})

    set(${path} "${outpath}" PARENT_SCOPE)
endfunction()

function(find_files files schema)
    file(GLOB_RECURSE _files RELATIVE ${CMAKE_SOURCE_DIR} ${schema})
    #message("${schema}: ${_files}")
    set(${files} ${_files} PARENT_SCOPE)
endfunction()

function(generate_file output template template_data)
    add_custom_command(
            OUTPUT ${output}
            COMMAND ${yasha.cmd} -o ${output}  -v ${template} ${template_data}
            COMMAND ${CMAKE_COMMAND}  -E copy  ${CMAKE_SOURCE_DIR}/${output} ${CMAKE_BINARY_DIR}/${output}
            DEPENDS ${template} ${template_data} ${yasha.deps}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating code. [${template} ==> ${output}]"
    )

    set_source_files_properties(${output} PROPERTIES GENERATED TRUE)
endfunction()

function (generate branch templates)
    MESSAGE(STATUS "configuring '${branch}' branch")

    foreach(template ${templates})

        preprocess_paths(impl_output impl ${template})
        preprocess_paths(test_output test ${template})

        # generate implementation files
        generate_file(${impl_output} ${template} ${type_template})
        list(APPEND generated_types ${impl_output})

        # generate test files
        generate_file(${test_output} ${template} ${test_template})
        list(APPEND generated_tests ${test_output})
    endforeach()

    add_custom_target(zacc.generate.${branch}.types
            DEPENDS ${generated_types}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    add_custom_target(zacc.generate.${branch}.tests
            DEPENDS ${generated_tests}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            )

    list(APPEND generate.types.all zacc.generate.${branch}.types)
    list(APPEND generate.tests.all zacc.generate.${branch}.tests)
endfunction()

file(GLOB_RECURSE templates    RELATIVE ${CMAKE_SOURCE_DIR}    "*${template.schema}")

function(add_test_target target branch files)
    add_executable("zacc.${branch}.tests" ${files})
    target_link_libraries("zacc.${branch}.tests" gtest_main)

    add_dependencies("zacc.${branch}.tests" "zacc.generate.${branch}.types" "zacc.generate.${branch}.tests" )

    target_compile_options("zacc.${branch}.tests" PUBLIC ${compiler_flags_${branch}})

    set(${target} "zacc.${branch}.tests" PARENT_SCOPE)
endfunction()

foreach(branch ${branches})
    if(${branch} MATCHES "sse*")
        find_files(templates "*/sse/*${template.schema}")
        find_files(files "*/sse/*${test.schema}")
    else()
        find_files(templates "*/${branch}/*${template.schema}")
        find_files(files "*/${branch}/*${test.schema}")
    endif()

    generate(${branch} "${templates}")

    add_test_target(test ${branch} "${files}")

    message("branch_defs: ${branch} - ${branch_defs_${branch}}")
    foreach(def ${branch_defs_${branch}})
        target_compile_definitions(zacc.${branch}.tests  PUBLIC "${def}=1")
    endforeach()

    list(APPEND tests ${test})
endforeach()

add_custom_target(zacc.generate.types.all DEPENDS ${generate.types.all})
add_custom_target(zacc.generate.tests.all DEPENDS ${generate.tests.all})
add_custom_target(zacc.generate.all DEPENDS zacc.generate.types.all zacc.generate.tests.all)
add_custom_target(zacc.tests.all DEPENDS ${tests})