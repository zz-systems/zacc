# SSE2 target ==========================================================================================================

zacc_target_metadata(sse.sse2
        COMPILE_FLAGS -msse2)

# SSE3 target ==========================================================================================================

zacc_target_metadata(sse.sse3
        COMPILE_FLAGS -msse3 -mssse3)

# SSE4.1 target ========================================================================================================

zacc_target_metadata(sse.sse41
        COMPILE_FLAGS -msse4.1)

# SSE4.1 + FMA3 target =================================================================================================

zacc_target_metadata(sse.sse41.fma3
        COMPILE_FLAGS -msse4.1 -mfma)

# SSE4.1 + FMA4 target =================================================================================================

zacc_target_metadata(sse.sse41.fma4
        COMPILE_FLAGS -msse4.1 -mfma4)
