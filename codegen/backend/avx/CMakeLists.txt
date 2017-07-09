# AVX interface ========================================================================================================

add_library(zacc.interface.avx.avx1 INTERFACE)
target_compile_options(zacc.interface.avx.avx1 INTERFACE -mavx)

add_library(zacc.interface.avx.avx1.defs INTERFACE)
target_compile_definitions(zacc.interface.avx.avx1.defs INTERFACE
        ZACC_MAJOR_BRANCH=avx
        ZACC_CAPABILITIES=avx1)

add_library(zacc.interface.avx.avx1.aggregate INTERFACE)
target_compile_definitions(zacc.interface.avx.avx1.aggregate INTERFACE
        ZACC_AVX=1)

target_link_libraries(zacc.interface.avx.avx1 INTERFACE zacc.interface.avx.avx1.aggregate zacc.interface.avx.avx1.defs zacc.interface.codegen)

# AVX + FMA interface ==================================================================================================

add_library(zacc.interface.avx.avx1.fma3 INTERFACE)
target_compile_options(zacc.interface.avx.avx1.fma3 INTERFACE -mavx -mfma)

add_library(zacc.interface.avx.avx1.fma3.defs INTERFACE)
target_compile_definitions(zacc.interface.avx.avx1.fma3.defs INTERFACE
        ZACC_MAJOR_BRANCH=avx
        ZACC_CAPABILITIES=avx1_fma3)

add_library(zacc.interface.avx.avx1.fma3.aggregate INTERFACE)
target_compile_definitions(zacc.interface.avx.avx1.fma3.aggregate INTERFACE
        ZACC_AVX=1)

target_link_libraries(zacc.interface.avx.avx1.fma3 INTERFACE zacc.interface.avx.avx1.fma3.aggregate zacc.interface.avx.avx1.fma3.defs zacc.interface.codegen)