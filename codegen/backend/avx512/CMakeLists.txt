# AVX512 interface =====================================================================================================

dispatchable_target_interface(avx.avx512
        ARCH avx512
        COMPILE_FLAGS -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)