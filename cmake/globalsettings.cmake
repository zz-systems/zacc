cmake_minimum_required(VERSION 3.6)

set(template.schema ".hpp.yml")
set(impl.schema ".impl.hpp")
set(test.schema ".test.cpp")

set(type_template "common/templates/type.impl.jinja")
set(test_template "common/templates/type.test.jinja")

set(codegen.cmd "C:/Python/Scripts/yasha")
set(codegen.deps
        "common/templates/type.py"
        "common/templates/type.test.yml"
        ${type_template}
        ${test_template}
        )

file(GLOB_RECURSE templates    RELATIVE ${CMAKE_SOURCE_DIR}    "*${template.schema}")