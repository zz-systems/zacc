# AVX2 interface =======================================================================================================

add_library(zacc.interface.avx2 INTERFACE)
target_translate_compile_options(zacc.interface.avx2 INTERFACE -mavx2 -mfma)

add_library(zacc.interface.avx2.defs INTERFACE)
target_compile_definitions(zacc.interface.avx2.defs INTERFACE
        ZACC_CAPABILITIES=avx2
        ZACC_MAJOR_BRANCH=avx2
        ZACC_AVX2=1)

target_link_libraries(zacc.interface.avx2 INTERFACE zacc.interface.avx2.defs)