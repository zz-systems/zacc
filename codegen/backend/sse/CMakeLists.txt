# SSE2 target ==========================================================================================================

dispatchable_target_interface(sse.sse2
        ARCH sse
        COMPILE_FLAGS -msse2)

# SSE3 target ==========================================================================================================

dispatchable_target_interface(sse.sse3
        ARCH sse
        COMPILE_FLAGS -msse3 -mssse3)

# SSE4.1 target ========================================================================================================

dispatchable_target_interface(sse.sse41
        ARCH sse
        COMPILE_FLAGS -msse4.1)

# SSE4.1 + FMA3 target =================================================================================================

dispatchable_target_interface(sse.sse41.fma3
        ARCH sse
        COMPILE_FLAGS -msse4.1 -mfma)

# SSE4.1 + FMA4 target =================================================================================================

dispatchable_target_interface(sse.sse41.fma4
        ARCH sse
        COMPILE_FLAGS -msse4.1 -mfma4)
