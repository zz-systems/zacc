# AVX2 target ==========================================================================================================

dispatchable_target_interface(avx.avx2
        ARCH avx2
        COMPILE_FLAGS -mavx2 -mfma)