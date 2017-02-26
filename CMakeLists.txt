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

include_directories(${CMAKE_SOURCE_DIR}/zacc)

include(${CMAKE_SOURCE_DIR}/tests/tests.cmake)
include(${CMAKE_SOURCE_DIR}/auxapps/auxapps.cmake)

set(template.schema ".hpp.yml")
set(impl.schema ".impl.hpp")
set(test.schema ".test.cpp")

set(yasha.cmd "C:/Python/Scripts/yasha")
set(yasha.deps
        "common/templates/type.py"
        "common/templates/type.test.yml"
        "common/templates/type.impl.jinja"
        "common/templates/type.test.jinja"
        )


option(BUILD_SCALAR_BRANCH "Build the scalar branch" ON)
option(BUILD_SSE_BRANCH "Build the sse branch" ON)
option(BUILD_AVX_BRANCH "Build the avx branch" ON)
option(BUILD_AVX2_BRANCH "Build the avx2 branch" ON)
option(BUILD_AVX512_BRANCH "Build the avx512 branch" OFF)

function(insert_dict_kv dict key value)
    set(${dict_${key}} "${value}")
endfunction()

insert_dict_kv(compiler_flags scalar "")
insert_dict_kv(compiler_flags sse -msse4)
insert_dict_kv(compiler_flags avx -mavx)
insert_dict_kv(compiler_flags avx2 -mavx2)
insert_dict_kv(compiler_flags avx512 -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)

if(BUILD_SCALAR_BRANCH)
    list(APPEND branches scalar)
endif()

if(BUILD_SSE_BRANCH)
    list(APPEND branches sse)
endif()

if(BUILD_AVX_BRANCH)
    list(APPEND branches avx)
endif()

if(BUILD_AVX2_BRANCH)
    list(APPEND branchesavx2)
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
    message("${schema}: ${_files}")
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

    set_source_files_properties(${gen_dir}/${output} PROPERTIES GENERATED TRUE)
endfunction()

function (generate branch)
    MESSAGE(STATUS "configuring '${branch}' branch")

    # Find templates for branch
    find_files(templates "*/${branch}/*${template.schema}")

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
endfunction()

file(GLOB_RECURSE templates    RELATIVE ${CMAKE_SOURCE_DIR}    "*${template.schema}")

set(type_template "common/templates/type.impl.jinja")
set(test_template "common/templates/type.test.jinja")

function(add_test_target target branch)
    find_files(tests "*/${branch}/*${template.schema}")

    add_executable("zacc.${branch}.tests" ${tests})
    target_link_libraries("zacc.${branch}.tests" gtest_main)

    add_dependencies("zacc.${branch}.tests" "zacc.generate.${branch}.types" "zacc.generate.${branch}.tests" )

    target_compile_options("zacc.${branch}.tests" PUBLIC ${compiler_flags_${branch}})

    set(${target} "zacc.${branch}.tests" PARENT_SCOPE)
endfunction()

foreach(branch ${branches})
    generate(${branch})
    add_test_target(test ${branch})

    list(APPEND tests ${test})
endforeach()

add_custom_target(zacc.tests.all DEPENDS ${tests})