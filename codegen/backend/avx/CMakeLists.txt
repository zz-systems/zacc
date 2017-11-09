# AVX target ===========================================================================================================

dispatchable_target_interface(avx.avx1
        ARCH avx
        COMPILE_FLAGS -mavx)

# AVX + FMA target =====================================================================================================

dispatchable_target_interface(avx.avx1.fma3
        ARCH avx
        COMPILE_FLAGS -mavx -mfma)