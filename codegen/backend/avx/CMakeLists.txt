# AVX target ===========================================================================================================

zacc_target_metadata(avx.avx1
        COMPILE_FLAGS -mavx)

# AVX + FMA target =====================================================================================================

zacc_target_metadata(avx.avx1.fma3
        COMPILE_FLAGS -mavx -mfma)