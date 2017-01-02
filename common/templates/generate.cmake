set(variable_defs)

macro(collect variable_def)
    set(variable_defs  ${variable_defs}   ${variable_def})
endmacro(collect)

macro (generate)

    list(LENGTH variable_defs variable_defs_count)
    math(EXPR variable_defs_count "${variable_defs_count} - 1")

    foreach(variable_def_index RANGE ${variable_defs_count})
        list(GET variable_defs  ${variable_def_index} variable_def)

        string(REGEX REPLACE ".hpp.yml" ".hpp" output ${variable_def})
        execute_process(
                COMMAND yasha -M common/templates/module.jinja
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE deps
        )
        string(REGEX REPLACE "^.*: " "" deps ${deps})
        string(REPLACE " " ";" deps ${deps})
        add_custom_command(
                OUTPUT ${output}
                COMMAND yasha -o ${output} ${template_impl}
                DEPENDS ${deps}
                COMMENT "Generating code for ${output}."
        )
    endforeach()
endmacro(generate)