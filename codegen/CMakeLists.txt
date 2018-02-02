file(GLOB_RECURSE templates    RELATIVE ${CMAKE_SOURCE_DIR}    "*${template.schema}")

set(template.schema ".hpp.yml")
set(impl.schema ".impl.hpp")
set(test.schema ".test.cpp")

set(type_template "codegen/templates/type.impl.jinja2")

set(codegen.cmd "${PYTHON_DIR}/Scripts/yasha.exe")

# fallback to PATH
if(EXISTS "${codegen.cmd}")
else()
    set(codegen.cmd "yasha")
endif()
set(codegen.ext "${CMAKE_CURRENT_LIST_DIR}/codegen/codegen.py")

#file(GLOB_RECURSE codegen.deps    RELATIVE ${CMAKE_SOURCE_DIR}    "codegen/*.py")

set(codegen.deps
        ${codegen.ext}
        ${CMAKE_CURRENT_LIST_DIR}/codegen/lexer.py
        ${CMAKE_CURRENT_LIST_DIR}/codegen/parser.py
        ${CMAKE_CURRENT_LIST_DIR}/codegen/renderer.py
        ${type_template}
        )

function(preprocess_paths path type template)
    string(REGEX REPLACE "${template.schema}" "${${type}.schema}" outpath ${template})
    string(REPLACE "codegen/" "" outpath ${outpath})

    set(${path} "${outpath}" PARENT_SCOPE)
endfunction()

function(find_files files schema)
    file(GLOB_RECURSE _files RELATIVE ${PROJECT_SOURCE_DIR} ${schema})
    set(${files} ${_files} PARENT_SCOPE)
endfunction()

macro(get_arch_files files branch schema)

    #parse_arch(${branch})

    set(arch ${${branch}.arch})

    find_files(_files "*/backend/${arch}/*${schema}")

    set(${files} ${_files})

endmacro()

function(generate_file output template template_data)
    get_filename_component(output_dir ${output} DIRECTORY)

    add_custom_command(
            OUTPUT ${PROJECT_SOURCE_DIR}/${output}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${output_dir}
            COMMAND ${codegen.cmd} -o ${PROJECT_SOURCE_DIR}/${output}  -v ${template} ${template_data} -e ${codegen.ext}
            COMMAND ${CMAKE_COMMAND}  -E copy  ${PROJECT_SOURCE_DIR}/${output} ${PROJECT_BINARY_DIR}/${output}
            DEPENDS ${template} ${template_data} ${codegen.deps}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "GEN ${template} ==> ${output}"
    )

    set_source_files_properties(${PROJECT_BINARY_DIR}/${output} PROPERTIES GENERATED TRUE)
    set_source_files_properties(${PROJECT_SOURCE_DIR}/${output} PROPERTIES GENERATED TRUE)
endfunction()

macro (generate branch templates)
    MESSAGE(STATUS "configuring '${branch}' branch with templates [${templates}]")

    foreach(template ${templates})

        preprocess_paths(impl_output impl ${template})
        preprocess_paths(test_output test ${template})

        set(impl_output "include/${impl_output}")
        set(test_output "test/${test_output}")

        # generate implementation files
        generate_file(${impl_output} ${template} ${type_template})
        list(APPEND generated_types ${PROJECT_SOURCE_DIR}/${impl_output})
    endforeach()

    list(APPEND zacc.codegen.types ${generated_types})
    list(APPEND zacc.codegen.tests ${generated_tests})
endmacro()

foreach(target ${branches})
    get_arch_files(templates ${target} ${template.schema})

    generate(${target} "${templates}")
endforeach()


add_custom_target(zacc.codegen.types.all ALL DEPENDS ${zacc.codegen.types} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_custom_target(zacc.codegen.tests.all ALL DEPENDS ${zacc.codegen.tests} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(zacc.codegen.all ALL DEPENDS zacc.codegen.types.all zacc.codegen.tests.all)

add_library(zacc.codegen INTERFACE)
add_dependencies(zacc.codegen zacc.codegen.types.all zacc.codegen.tests.all)

#add_custom_target(zacc.codegen.all DEPENDS zacc.codegen)