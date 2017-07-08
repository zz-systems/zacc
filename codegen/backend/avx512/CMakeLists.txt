# AVX512 interface =====================================================================================================

add_library(zacc.interface.avx512 INTERFACE)
target_compile_options(zacc.interface.avx512 INTERFACE -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)


add_library(zacc.interface.avx512.defs INTERFACE)
target_compile_definitions(zacc.interface.avx512.defs INTERFACE
        ZACC_CAPABILITIES=avx512
        ZACC_MAJOR_BRANCH=avx512
        ZACC_AVX512=1)

target_link_libraries(zacc.interface.avx512 INTERFACE zacc.interface.avx512.defs)