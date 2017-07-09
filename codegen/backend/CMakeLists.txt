
function(create_branch_interface branch)
    add_library(zacc.interface.${branch} INTERFACE)
    target_compile_options(zacc.interface.${branch} INTERFACE -mavx2 -mfma)

    add_library(zacc.interface.${branch}.defs INTERFACE)
    target_compile_definitions(zacc.interface.${branch}.defs INTERFACE
            ZACC_MAJOR_BRANCH=avx2
            ZACC_CAPABILITIES=avx2)

    add_library(zacc.interface.${branch}.aggregate INTERFACE)
    target_compile_definitions(zacc.interface.${branch}.aggregate INTERFACE
            ZACC_AVX2=1)

    target_link_libraries(zacc.interface.${branch} INTERFACE zacc.interface.${branch}.aggregate zacc.interface.${branch}.defs zacc.interface.codegen)
endfunction()


add_subdirectory(scalar)
add_subdirectory(sse)
add_subdirectory(avx)
add_subdirectory(avx2)
add_subdirectory(avx512)