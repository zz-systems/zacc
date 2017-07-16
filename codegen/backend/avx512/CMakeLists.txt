# AVX512 interface =====================================================================================================

zacc_target_metadata(avx.avx512
        MAJOR_TARGET avx512
        COMPILE_FLAGS -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)