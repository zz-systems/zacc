cmake_minimum_required(VERSION 3.6)
project(zacc)

set(CMAKE_VERBOSE_MAKEFILE Off)
# options ==============================================================================================================

option(BUILD_SCALAR_BRANCH "Build the scalar branch" ON)
option(BUILD_SSE_BRANCH "Build the sse branch" ON)
option(BUILD_AVX_BRANCH "Build the avx branch" ON)
option(BUILD_AVX2_BRANCH "Build the avx2 branch" ON)
option(BUILD_AVX512_BRANCH "Build the avx512 branch" OFF)
option(BUILD_OPENCL_BRANCH "Build the OpenCL branch" OFF)

option(ENABLE_TRACE "Enable tracing (EXTREMELY SLOW!)" OFF)

option(BUILD_TEST "Build the tests" ON)
option(BUILD_DOC "Build the documentation" OFF)

option(BUILD_FAST_FLOAT "Build with relaxed IEEE754 options. Faster and less precise" Off)

option(BUILD_CI_TEST "Build tests for CI environments" Off)

# util =================================================================================================================

macro(insert_kv dict key)
    set("${dict}_${key}" ${ARGN})
endmacro()

macro(get_branch_files files branch schema)
    # sse.sse4 => [major; minor] => [sse; sse4]
    string(REPLACE "." ";" parts ${branch})
    list(LENGTH parts len)
    if(${len} GREATER 1) # majorbranch.subbranch.ignored.ignored
        list(GET parts 0 majorbranch)

        find_files(_files "*/backend/${majorbranch}/*${schema}")

    elseif(${len} EQUAL 1) # majorbranch
        find_files(_files "*/backend/${branch}/*${schema}")
    else()
        message(FATAL_ERROR "malformed branch definition")
    endif()

    set(${files} ${_files})
endmacro()

# compiler config ======================================================================================================

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Clang doesn't support the __float128 type. Here are some workarounds:
# https://bugs.llvm.org//show_bug.cgi?id=13530#c3
# 1) build with -D__STRICT_ANSI__
# 2) edit bits/c++config.h (somewhere inside /usr/include/c++/4.7.0) so it doesn't define _GLIBCXX_USE_FLOAT128
# 3) configure libstdc++ with clang instead of gcc
# 4) add 'struct __float128;' before you include any STL header
add_definitions(-D__STRICT_ANSI__)

if(ENABLE_TRACE)
    add_definitions(-DZACC_TRACE)
    message("Adding trace")
endif()

if(BUILD_FAST_FLOAT)
    add_definitions(-DZACC_FAST_FLOAT=true)
else()
    add_definitions(-DZACC_FAST_FLOAT=false)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

insert_kv(branch_flags  scalar              "")
insert_kv(branch_flags  sse.sse2            -msse2)
insert_kv(branch_flags  sse.sse3            -msse3 -mssse3)

insert_kv(branch_flags  sse.sse41           -msse4.1)
insert_kv(branch_flags  sse.sse41.fma3      -msse4.1 -mfma)
insert_kv(branch_flags  sse.sse41.fma4      -msse4.1 -mfma4)

#insert_kv(branch_flags  sse.sse42      -msse4.1 -msse4.2)
#insert_kv(branch_flags  sse.sse42.fma3 -msse4.1 -msse4.2 -mfma)
#insert_kv(branch_flags  sse.sse42.fma4 -msse4.1 -msse4.2 -mfma4)

insert_kv(branch_flags  avx           -mavx -mfma)
insert_kv(branch_flags  avx2          -mavx2 -mfma)
insert_kv(branch_flags  avx512        -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)

insert_kv(branch_defs   scalar          ZACC_CAPABILITIES=0b000000000000        ZACC_MAJOR_BRANCH=scalar    ZACC_SCALAR=1)
insert_kv(branch_defs   sse.sse2        ZACC_CAPABILITIES=0b000000000001        ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)
insert_kv(branch_defs   sse.sse3        ZACC_CAPABILITIES=0b000000000111        ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)

insert_kv(branch_defs  sse.sse41        ZACC_CAPABILITIES=0b000000001111        ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)
insert_kv(branch_defs  sse.sse41.fma3   ZACC_CAPABILITIES=0b000000101111        ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)
insert_kv(branch_defs  sse.sse41.fma4   ZACC_CAPABILITIES=0b000001001111        ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)

insert_kv(branch_defs   avx             ZACC_CAPABILITIES=0b000010101111        ZACC_MAJOR_BRANCH=avx       ZACC_AVX=1)
insert_kv(branch_defs   avx2            ZACC_CAPABILITIES=0b000110101111        ZACC_MAJOR_BRANCH=avx2      ZACC_AVX2=1)
insert_kv(branch_defs   avx512          ZACC_CAPABILITIES=0b001110101111        ZACC_MAJOR_BRANCH=avx512    ZACC_AVX512=1)

# branch config ========================================================================================================

if(BUILD_SCALAR_BRANCH)
    list(APPEND branches scalar)
endif()

if(BUILD_SSE_BRANCH)
    list(APPEND branches sse.sse2)
    list(APPEND branches sse.sse3)
    list(APPEND branches sse.sse41)
    list(APPEND branches sse.sse41.fma3)
    list(APPEND branches sse.sse41.fma4)
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

# packages =============================================================================================================

#find_package(GTest REQUIRED)
#include_directories(
#        ${GTEST_INCLUDE_DIRS}
#        ${GMOCK_INCLUDE_DIRS}
#)

# BUILD! ===============================================================================================================

# fetch gtest
include(test/tests.cmake)

# add codegen targets
include(codegen/CMakeLists.txt)

# add app targets
include(src/CMakeLists.txt)

# add test targets
include(test/CMakeLists.txt)

# add documentation targets
include(doc/CMakeLists.txt)