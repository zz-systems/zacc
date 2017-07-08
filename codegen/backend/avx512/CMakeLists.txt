# AVX512 interface =====================================================================================================

add_library(zacc.interface.avx512 INTERFACE)

if(CLANG_CL)
    target_compile_options(zacc.interface.avx512 INTERFACE
            -Xclang -mavx512f
            -Xclang -mavx512pf
            -Xclang -mavx512er
            -Xclang -mavx512cd
            -Xclang -mavx512vl
            -Xclang -mavx512bw
            -Xclang -mavx512dq)
else()
    target_compile_options(zacc.interface.avx512 INTERFACE -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)
endif()

add_library(zacc.interface.avx512.defs INTERFACE)
target_compile_definitions(zacc.interface.avx512.defs INTERFACE
        ZACC_CAPABILITIES=avx512
        ZACC_MAJOR_BRANCH=avx512
        ZACC_AVX512=1)

target_link_libraries(zacc.interface.avx512 INTERFACE zacc.interface.avx512.defs)