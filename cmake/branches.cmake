cmake_minimum_required(VERSION 3.6)

#include(${CMAKE_SOURCE_DIR}/cmake/util.cmake)
#include(${CMAKE_SOURCE_DIR}/cmake/options.cmake)

insert_kv(branch_flags  scalar         "")
insert_kv(branch_flags  sse.sse2      -msse2)
insert_kv(branch_flags  sse.sse3      -msse3 -mssse3)
insert_kv(branch_flags  sse.sse4      -msse4.1 -msse4.2)
insert_kv(branch_flags  sse.sse4fma   -msse4.1 -msse4.2 -mfma)
insert_kv(branch_flags  avx           -mavx)
insert_kv(branch_flags  avx2          -mavx2)
insert_kv(branch_flags  avx512        -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)

insert_kv(branch_defs   scalar       ZACC_SCALAR)
insert_kv(branch_defs   sse.sse2     ZACC_SSE2)
insert_kv(branch_defs   sse.sse3     ZACC_SSE2 ZACC_SSE3)
insert_kv(branch_defs   sse.sse4     ZACC_SSE2 ZACC_SSE3 ZACC_SSE4)
insert_kv(branch_defs   sse.sse4fma  ZACC_SSE2 ZACC_SSE3 ZACC_SSE4 ZACC_SSE4FMA)
insert_kv(branch_defs   avx          ZACC_AVX)
insert_kv(branch_defs   avx2         ZACC_AVX2)
insert_kv(branch_defs   avx512       ZACC_AVX2)


if(BUILD_SCALAR_BRANCH)
    list(APPEND branches scalar)
endif()

if(BUILD_SSE_BRANCH)
    list(APPEND branches sse.sse2)
    list(APPEND branches sse.sse3)
    list(APPEND branches sse.sse4)
    list(APPEND branches sse.sse4fma)
endif()

if(BUILD_AVX_BRANCH)
    list(APPEND branches avx)
endif()

if(BUILD_AVX2_BRANCH)
    list(APPEND branches avx2)
endif()

if(BUILD_AVX512_BRANCH)
    list(APPEND branches avx512)
endif()

if(BUILD_OPENCL_BRANCH)
    list(APPEND branches openCL)
endif()