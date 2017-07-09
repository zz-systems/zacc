# AVX2 interface =======================================================================================================

add_library(zacc.interface.avx.avx2 INTERFACE)
target_compile_options(zacc.interface.avx.avx2 INTERFACE -mavx2 -mfma)

add_library(zacc.interface.avx.avx2.defs INTERFACE)
target_compile_definitions(zacc.interface.avx.avx2.defs INTERFACE
        ZACC_MAJOR_BRANCH=avx2
        ZACC_CAPABILITIES=avx2)

add_library(zacc.interface.avx.avx2.aggregate INTERFACE)
target_compile_definitions(zacc.interface.avx.avx2.aggregate INTERFACE
        ZACC_AVX2=1)

target_link_libraries(zacc.interface.avx.avx2 INTERFACE zacc.interface.avx.avx2.aggregate zacc.interface.avx.avx2.defs zacc.interface.codegen)
