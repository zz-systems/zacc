
function(zacc_target_metadata target)
    set(options)
    set(oneValueArgs MAJOR_TARGET CAPABILITIES)
    set(multiValueArgs COMPILE_FLAGS BRANCH_DEFS AGGREGATE_DEFS)

    cmake_parse_arguments(create_branch_interface "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    message(STATUS "Configuring target ${target}")

    # parse target

    string(REPLACE "." ";" parts ${target})
    list(LENGTH parts len)

    if(${len} GREATER 1) # majorbranch.subbranch.ignored.ignored
        list(GET parts 0 major)
        list(REMOVE_AT parts 0)

        string (REPLACE ";" "_" capability "${parts}")

        string(TOUPPER "${major}" major_target_definition)
    elseif(${len} EQUAL 1)
        list(GET parts 0 major)
        string (REPLACE ";" "_" capability "${parts}")
    else()
        message(FATAL_ERROR "malformed branch definition")
    endif()

    if(create_branch_interface_MAJOR_TARGET)
        set(major ${create_branch_interface_MAJOR_TARGET})
    endif()


    string(TOUPPER "${major}" major_target_definition)

    add_library(zacc.interface.${target} INTERFACE)
    add_library(zacc.interface.${target}.private INTERFACE)
    add_library(zacc.interface.${target}.interface INTERFACE)

    target_compile_options(
            zacc.interface.${target}
            INTERFACE
                ${create_branch_interface_COMPILE_FLAGS}
    )


    target_compile_definitions(
            zacc.interface.${target}.private
            INTERFACE
                ZACC_MAJOR_BRANCH=${major}
                ZACC_CAPABILITIES=${capability}
                ${create_branch_interface_BRANCH_DEFS}
    )



    target_compile_definitions(
            zacc.interface.${target}.interface
            INTERFACE
                ZACC_${major_target_definition}=1
                ${create_branch_interface_AGGREGATE_DEFS}
    )

    target_link_libraries(
            zacc.interface.${target}
            INTERFACE
                zacc.interface.${target}.interface
                zacc.interface.${target}.private
                zacc.interface.codegen
    )

endfunction()


add_subdirectory(scalar)
add_subdirectory(sse)
add_subdirectory(avx)
add_subdirectory(avx2)
add_subdirectory(avx512)