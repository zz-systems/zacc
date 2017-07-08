# AVX interface ========================================================================================================

add_library(zacc.interface.avx INTERFACE)
target_compile_options(zacc.interface.avx INTERFACE -mavx -mfma)
target_compile_definitions(zacc.interface.avx INTERFACE
        ZACC_MAJOR_BRANCH=avx)

add_library(zacc.interface.avx.defs INTERFACE)
target_compile_definitions(zacc.interface.avx.defs INTERFACE
        ZACC_CAPABILITIES=avx1
        ZACC_AVX=1)

target_link_libraries(zacc.interface.avx INTERFACE zacc.interface.avx.defs zacc.interface.codegen)