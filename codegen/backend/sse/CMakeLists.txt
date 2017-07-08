# SSE2 interface =======================================================================================================

add_library(zacc.interface.sse.sse2 INTERFACE)

if(CLANG_CL)
    target_compile_options(zacc.interface.sse.sse2 INTERFACE -Xclang -msse2)
else()
    target_compile_options(zacc.interface.sse.sse2 INTERFACE -mavx)
endif()

target_translate_compile_options(zacc.interface.sse.sse2 INTERFACE -msse2)

add_library(zacc.interface.sse.sse2.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse2.defs INTERFACE
        ZACC_CAPABILITIES=sse2
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse2 INTERFACE zacc.interface.sse.sse2.defs)

# SSE3 interface =======================================================================================================

add_library(zacc.interface.sse.sse3 INTERFACE)

if(CLANG_CL)
    target_compile_options(zacc.interface.sse.sse3 INTERFACE -Xclang -msse3)
    target_compile_options(zacc.interface.sse.sse3 INTERFACE -Xclang -mssse3)
else()
    target_compile_options(zacc.interface.sse.sse3 INTERFACE -msse3 -mssse3)
endif()

add_library(zacc.interface.sse.sse3.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse3.defs INTERFACE
        ZACC_CAPABILITIES=sse3
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse3 INTERFACE zacc.interface.sse.sse3.defs)

# SSE4.1 interface =====================================================================================================

add_library(zacc.interface.sse.sse41 INTERFACE)

if(CLANG_CL)
    target_compile_options(zacc.interface.sse.sse41 INTERFACE -Xclang -msse4.1)
else()
    target_compile_options(zacc.interface.sse.sse41 INTERFACE -msse4.1)
endif()

target_translate_compile_options(zacc.interface.sse.sse41 INTERFACE -msse4.1)

add_library(zacc.interface.sse.sse41.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse41.defs INTERFACE
        ZACC_CAPABILITIES=sse41
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse41 INTERFACE zacc.interface.sse.sse41.defs)

# SSE4.1 + FMA3 interface ==============================================================================================

add_library(zacc.interface.sse.sse41.fma3 INTERFACE)

if(CLANG_CL)
    target_compile_options(zacc.interface.sse.sse41.fma3 INTERFACE -Xclang -msse4.1)
    target_compile_options(zacc.interface.sse.sse41.fma3 INTERFACE -Xclang -mfma)
else()
    target_compile_options(zacc.interface.sse.sse41.fma3 INTERFACE -msse4.1 -mfma)
endif()

add_library(zacc.interface.sse.sse41.fma3.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse41.fma3.defs INTERFACE
        ZACC_CAPABILITIES=sse41_fma3
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse41.fma3 INTERFACE zacc.interface.sse.sse41.fma3.defs)

# SSE4.1 + FMA4 interface ==============================================================================================

add_library(zacc.interface.sse.sse41.fma4 INTERFACE)

if(CLANG_CL)
    target_compile_options(zacc.interface.sse.sse41.fma4 INTERFACE -Xclang -msse4.1)
    target_compile_options(zacc.interface.sse.sse41.fma4 INTERFACE -Xclang -mfma4)
else()
    target_compile_options(zacc.interface.sse.sse41.fma4 INTERFACE -msse4.1 -mfma4)
endif()

add_library(zacc.interface.sse.sse41.fma4.defs INTERFACE)
target_compile_definitions(zacc.interface.sse.sse41.fma4.defs INTERFACE
        ZACC_CAPABILITIES=sse41_fma4
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

target_link_libraries(zacc.interface.sse.sse41.fma4 INTERFACE zacc.interface.sse.sse41.fma4.defs)