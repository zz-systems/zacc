# SSE2 interface =======================================================================================================

add_library(zacc.interface.sse.sse2 INTERFACE)
target_compile_options(zacc.interface.sse.sse2 INTERFACE -msse2)

add_library(zacc.interface.sse.sse2.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse2.defs INTERFACE
        ZACC_MAJOR_BRANCH=sse
        ZACC_CAPABILITIES=sse2)

add_library(zacc.interface.sse.sse2.aggregate INTERFACE)
target_compile_definitions(zacc.interface.sse.sse2.aggregate INTERFACE
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse2 INTERFACE zacc.interface.sse.sse2.aggregate zacc.interface.sse.sse2.defs zacc.interface.codegen)

# SSE3 interface =======================================================================================================

add_library(zacc.interface.sse.sse3 INTERFACE)
target_compile_options(zacc.interface.sse.sse3 INTERFACE -msse3 -mssse3)

add_library(zacc.interface.sse.sse3.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse3.defs INTERFACE
        ZACC_MAJOR_BRANCH=sse
        ZACC_CAPABILITIES=sse3)

add_library(zacc.interface.sse.sse3.aggregate INTERFACE)
target_compile_definitions(zacc.interface.sse.sse3.aggregate INTERFACE
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse3 INTERFACE zacc.interface.sse.sse3.aggregate zacc.interface.sse.sse3.defs zacc.interface.codegen)

# SSE4.1 interface =====================================================================================================

add_library(zacc.interface.sse.sse41 INTERFACE)
target_compile_options(zacc.interface.sse.sse41 INTERFACE -msse4.1)

add_library(zacc.interface.sse.sse41.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse41.defs INTERFACE
        ZACC_MAJOR_BRANCH=sse
        ZACC_CAPABILITIES=sse41)

add_library(zacc.interface.sse.sse41.aggregate INTERFACE)
target_compile_definitions(zacc.interface.sse.sse41.aggregate INTERFACE
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse41 INTERFACE zacc.interface.sse.sse41.aggregate zacc.interface.sse.sse41.defs zacc.interface.codegen)

# SSE4.1 + FMA3 interface ==============================================================================================

add_library(zacc.interface.sse.sse41.fma3 INTERFACE)
target_compile_options(zacc.interface.sse.sse41.fma3 INTERFACE -msse4.1 -mfma)

add_library(zacc.interface.sse.sse41.fma3.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse41.fma3.defs INTERFACE
        ZACC_MAJOR_BRANCH=sse
        ZACC_CAPABILITIES=sse41_fma3)

add_library(zacc.interface.sse.sse41.fma3.aggregate INTERFACE)
target_compile_definitions(zacc.interface.sse.sse41.fma3.aggregate INTERFACE
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse41.fma3 INTERFACE zacc.interface.sse.sse41.fma3.aggregate zacc.interface.sse.sse41.fma3.defs zacc.interface.codegen)

# SSE4.1 + FMA4 interface ==============================================================================================

add_library(zacc.interface.sse.sse41.fma4 INTERFACE)
target_compile_options(zacc.interface.sse.sse41.fma4 INTERFACE -msse4.1 -mfma4)

add_library(zacc.interface.sse.sse41.fma4.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse41.fma4.defs INTERFACE
        ZACC_MAJOR_BRANCH=sse
        ZACC_CAPABILITIES=sse41_fma4)

add_library(zacc.interface.sse.sse41.fma4.aggregate INTERFACE)
target_compile_definitions(zacc.interface.sse.sse41.fma4.aggregate INTERFACE
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse41.fma4 INTERFACE zacc.interface.sse.sse41.fma4.aggregate zacc.interface.sse.sse41.fma4.defs zacc.interface.codegen)
