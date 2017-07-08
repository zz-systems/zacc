# AVX interface ========================================================================================================

add_library(zacc.interface.avx INTERFACE)

if(CLANG_CL)
    target_compile_options(zacc.interface.avx INTERFACE -Xclang -mavx -Xclang -mfma)
else()
    target_compile_options(zacc.interface.avx INTERFACE -mavx -mfma)
endif()

add_library(zacc.interface.avx.defs INTERFACE)
target_compile_definitions(zacc.interface.avx.defs INTERFACE
        ZACC_CAPABILITIES=avx1
        ZACC_MAJOR_BRANCH=avx
        ZACC_AVX=1)

target_link_libraries(zacc.interface.avx INTERFACE zacc.interface.avx.defs)