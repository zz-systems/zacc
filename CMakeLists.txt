cmake_minimum_required(VERSION 3.6)
project(zacc)

include_directories(${CMAKE_SOURCE_DIR}/zacc)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE sources           RELATIVE ${CMAKE_SOURCE_DIR}    "*.cpp")
file(GLOB_RECURSE templates         RELATIVE ${CMAKE_SOURCE_DIR}    "*.jinja")
file(GLOB_RECURSE templates_impl    RELATIVE ${CMAKE_SOURCE_DIR}    "*.hpp.yml")

# build type templates
foreach(template_impl ${templates_impl})
    string(REGEX REPLACE ".hpp.yml" ".gen.hpp" output ${template_impl})
    string(REPLACE "config/" "generated/" output ${output})

    execute_process(
            COMMAND C:/Python/Scripts/yasha -M common/templates/module.jinja
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE deps
    )

    string(REGEX REPLACE "^.*: " "" deps ${deps})
    string(REPLACE " " ";" deps ${deps})

    message(${deps})
    message(${output})
    message(${template_impl})

    add_custom_command(
            OUTPUT ${output}
            COMMAND C:/Python/Scripts/yasha -o ${output} -v ${template_impl} common/templates/module.jinja
            DEPENDS ${deps}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating code for ${output}."
    )

    list(APPEND generated ${output})
endforeach()

add_custom_target(generate DEPENDS ${generated})

add_executable(zacc ${SOURCE_FILES} tests/test.cpp)

target_compile_options(zacc PUBLIC -msse2 -msse3 -mssse3 -msse4)