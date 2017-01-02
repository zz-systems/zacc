cmake_minimum_required(VERSION 3.6)
project(zacc)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE sources       "*.cpp")
file(GLOB_RECURSE templates     "*.jinja")
file(GLOB_RECURSE templates_impl "*.hpp.yml")

# build type templates
foreach(template_impl ${templates_impl})
    string(REGEX REPLACE ".hpp.yml" ".hpp" output ${template_impl})
    execute_process(
            COMMAND yasha -M common/templates/module.jinja
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE deps
    )
    #string(REGEX REPLACE "^.*: " "" deps ${deps})
    #string(REPLACE " " ";" deps ${deps})
    add_custom_command(
            OUTPUT ${output}
            COMMAND yasha -o ${output} ${template_impl}
            DEPENDS ${deps}
            COMMENT "Generating code for ${output}."
    )
endforeach()

add_executable(zacc ${SOURCE_FILES} tests/test.cpp)

target_compile_options(zacc PUBLIC -msse2 -msse3 -mssse3 -msse4)