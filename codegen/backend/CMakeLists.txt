function(parse_arch target)
    # split by '.'
    string(REPLACE "." ";" parts ${target})
    list(LENGTH parts len)

    # parse target into major arch, sub arch, capability ...
    if(${len} GREATER 1) # majorbranch.subbranch.capability...
        list(GET parts 0 _arch)
        list(REMOVE_AT parts 0)
    elseif(${len} EQUAL 1)
        list(GET parts 0 _arch)
    else()
        message(FATAL_ERROR "malformed branch definition")
    endif()

    # get capability (target name without major arch)
    string(REPLACE ";" "_" _capability "${parts}")

    set(arch ${_arch} PARENT_SCOPE)
    set(capability ${_capability} PARENT_SCOPE)
endfunction()

function(dispatchable_target_interface target)
    ### parse args
    set(options)
    set(oneValueArgs ARCH CAPABILITIES)
    set(multiValueArgs COMPILE_FLAGS BRANCH_DEFS AGGREGATE_DEFS)

    cmake_parse_arguments(create_branch_interface "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    message(STATUS "Configuring target ${target}")


    ### parse arch

    parse_arch(${target})

    # override arch if value provided
    if(create_branch_interface_ARCH)
        set(arch ${create_branch_interface_ARCH})
    endif()

    # store major architecture in cache for later usage
    set(${target}.arch ${arch} CACHE INTERNAL "Major architecture for particular target")

    # set to upper for macros
    string(TOUPPER "${arch}" major_arch_definition)

    ### create interface libraries

    # set shared names
    set(zacc_static_dispatch
        zacc.dispatch.${target}.static)

    set(zacc_dynamic_dispatch
        zacc.dispatch.${target}.dynamic)

    set(zacc_arch
        zacc.dispatch.${target})

    # provides macros for compile time dispatching
    add_library(${zacc_static_dispatch} INTERFACE)

    target_compile_definitions(
        ${zacc_static_dispatch}
        INTERFACE
            ZACC_MAJOR_ARCH=${arch}
            ZACC_ARCH=${capability}
            ZACC_HAS_VECTORS=1
            ${create_branch_interface_BRANCH_DEFS}
    )

    # provides macros for run- and compiletime dispatching
    add_library(${zacc_dynamic_dispatch} INTERFACE)

    target_compile_definitions(
        ${zacc_dynamic_dispatch}
        INTERFACE
            ZACC_${major_arch_definition}=1
            ${create_branch_interface_AGGREGATE_DEFS}
    )

    # provides compile flags
    add_library(${zacc_arch} INTERFACE)

    target_compile_options(
        ${zacc_arch}
        INTERFACE
            ${create_branch_interface_COMPILE_FLAGS}
    )

    # put it together

    target_link_libraries(
        ${zacc_arch}
        INTERFACE
            ${zacc_static_dispatch}
            ${zacc_dynamic_dispatch}
            zacc.codegen
    )

endfunction()


add_subdirectory(scalar)
add_subdirectory(sse)
add_subdirectory(avx)
add_subdirectory(avx2)
add_subdirectory(avx512)