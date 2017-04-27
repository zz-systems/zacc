set(template.schema ".hpp.yml")
set(impl.schema ".impl.hpp")
set(test.schema ".test.cpp")

set(type_template "codegen/templates/type.impl.jinja")
set(test_template "codegen/templates/type.test.jinja")

file(GLOB_RECURSE templates    RELATIVE ${CMAKE_SOURCE_DIR}    "*${template.schema}")

set(codegen.cmd "${PYTHON_BIN}\\Scripts\\yasha")
set(codegen.ext "codegen/engine/codegen.py")

set(codegen.deps
        "${codegen.ext}"
        "codegen/config/type.test.yml"
        ${type_template}
        ${test_template}
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

function(generate_file output template template_data)
    get_filename_component(output_dir ${output} DIRECTORY)

    add_custom_command(
            OUTPUT ${PROJECT_SOURCE_DIR}/${output}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${output_dir}
            COMMAND ${codegen.cmd} -o ${output}  -v ${template} ${template_data} -e ${codegen.ext}
            COMMAND ${CMAKE_COMMAND}  -E copy  ${PROJECT_SOURCE_DIR}/${output} ${PROJECT_BINARY_DIR}/${output}
            DEPENDS ${template} ${template_data} ${codegen.deps}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "GEN ${template} ==> ${output}"
    )

    set_source_files_properties(${output} PROPERTIES GENERATED TRUE)
    set_source_files_properties(${PROJECT_SOURCE_DIR}/${output} PROPERTIES GENERATED TRUE)
endfunction()

function (generate branch templates)
    MESSAGE(STATUS "configuring '${branch}' branch with templates [${templates}]")

    foreach(template ${templates})

        preprocess_paths(impl_output impl ${template})
        preprocess_paths(test_output test ${template})

        set(impl_output "include/${impl_output}")
        set(test_output "test/${test_output}")

        # generate implementation files
        generate_file(${impl_output} ${template} ${type_template})
        list(APPEND generated_types ${PROJECT_SOURCE_DIR}/${impl_output})

        # generate test files
        generate_file(${test_output} ${template} ${test_template})
        list(APPEND generated_tests ${PROJECT_SOURCE_DIR}/${test_output})
    endforeach()

    add_custom_target(zacc.generate.${branch}.types
            DEPENDS ${generated_types}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

    add_custom_target(zacc.generate.${branch}.tests
            DEPENDS ${generated_tests}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endfunction()

foreach(branch ${branches})
    get_branch_files(templates ${branch} "${template.schema}")

    generate(${branch} "${templates}")

    list(APPEND generate.types.all zacc.generate.${branch}.types)
    list(APPEND generate.tests.all zacc.generate.${branch}.tests)
endforeach()

add_custom_target(zacc.generate.types.all ALL DEPENDS ${generate.types.all})
add_custom_target(zacc.generate.tests.all ALL DEPENDS ${generate.tests.all})
add_custom_target(zacc.generate.all ALL DEPENDS zacc.generate.types.all zacc.generate.tests.all)