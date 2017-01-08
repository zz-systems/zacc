cmake_minimum_required(VERSION 3.6)
project(zacc)

#include(${CMAKE_SOURCE_DIR}/common/templates/generate.cmake)
include(${CMAKE_SOURCE_DIR}/tests/tests.cmake)
include_directories(${CMAKE_SOURCE_DIR}/zacc)

set(CMAKE_CXX_STANDARD 14)

set(template.schema ".hpp.yml")
set(impl.schema ".impl.hpp")
set(test.schema ".test.cpp")

set(gen_dir "${PROJECT_BINARY_DIR}/generated")

file(GLOB_RECURSE templates    RELATIVE ${CMAKE_SOURCE_DIR}    "*${template.schema}")

file(GLOB_RECURSE type_template RELATIVE ${CMAKE_SOURCE_DIR} "type.impl.jinja")
file(GLOB_RECURSE test_template RELATIVE ${CMAKE_SOURCE_DIR} "type.test.jinja")


foreach(template ${templates})
    string(REGEX REPLACE "${template.schema}" "${impl.schema}" impl_output ${template})
    string(REGEX REPLACE "${template.schema}" "${test.schema}" test_output ${template})

    string(REPLACE "config/" "impl/" impl_output ${impl_output})
    string(REPLACE "config/" "test/" test_output ${test_output})

    execute_process(
            COMMAND C:/Python/Scripts/yasha -M ${type_template}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE deps
    )

    string(REGEX REPLACE "^.*: " "" deps ${deps})
    string(REPLACE " " ";" deps ${deps})

    # generate implementation files
    add_custom_command(
            OUTPUT ${impl_output}
            COMMAND C:/Python/Scripts/yasha -o ${impl_output} -v ${template} ${type_template}
            DEPENDS ${deps}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating implementation code. [${template} ==> ${impl_output}]"
    )
    list(APPEND generated_types ${impl_output})

    # generate test files
    add_custom_command(
            OUTPUT ${test_output}
            COMMAND C:/Python/Scripts/yasha -o ${test_output} -v ${template} ${test_template}
            DEPENDS ${deps}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating test code. [${template} ==> ${test_output}]"
    )

    list(APPEND generated_tests ${test_output})
endforeach()

set_source_files_properties(${generated_tests}
        PROPERTIES GENERATED TRUE)

# make codegen targets
add_custom_target(zacc.generate.types DEPENDS ${generated_types})
add_custom_target(zacc.generate.tests DEPENDS ${generated_tests})

add_custom_target(zacc.generate.all DEPENDS zacc.generate.types zacc.generate.tests)

# make test target
file(GLOB_RECURSE tests    ABSOLUTE ${CMAKE_SOURCE_DIR}    "*/scalar/*${test.schema}")
message("${tests}")
set_source_files_properties(${tests}
        PROPERTIES GENERATED TRUE)

add_executable(zacc.tests ${tests})
add_dependencies(zacc.tests zacc.generate.types zacc.generate.tests)
target_link_libraries(zacc.tests gtest_main)
target_compile_options(zacc.tests PUBLIC -msse2 -msse3 -mssse3 -msse4)


#add_test(NAME zacc-tests COMMAND zacc-tests)