cmake_minimum_required(VERSION 3.6)

#include(${CMAKE_SOURCE_DIR}/cmake/globalsettings.cmake)

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

function(find_templates templates)
    find_files(_templates "*${template.schema}")
    set(${templates} ${_templates} PARENT_SCOPE)
endfunction()

function(generate_file output template template_data)
    add_custom_command(
            OUTPUT ${output}
            COMMAND ${codegen.cmd} -o ${output}  -v ${template} ${template_data}
            COMMAND ${CMAKE_COMMAND}  -E copy  ${CMAKE_SOURCE_DIR}/${output} ${CMAKE_BINARY_DIR}/${output}
            DEPENDS ${template} ${template_data} ${codegen.deps}
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