cmake_minimum_required(VERSION 3.6)
project(zacc)

include(cmake/shared.cmake)

#=======================================================================================================================
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

function(target_native_compile_options target)
    set(options OPTIONAL ZACC_FAST_FLOAT)
    set(oneValueArgs "")
    set(multiValueArgs PUBLIC PRIVATE INTERFACE)

    cmake_parse_arguments(opt "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if(CLANG_CL)
        set(prefix -Xclang)
    endif()

    foreach(flag ${opt_PRIVATE})
        target_compile_options(${target} PRIVATE ${prefix} ${flag})
    endforeach()

    foreach(flag ${opt_PUBLIC})
        target_compile_options(${target} PUBLIC ${prefix} ${flag})
    endforeach()

    foreach(flag ${opt_INTERFACE})
        target_compile_options(${target} INTERFACE ${prefix} ${flag})
    endforeach()
endfunction()



add_library(zacc.interface.scalar INTERFACE)
target_compile_definitions(zacc.interface.scalar INTERFACE
        ZACC_CAPABILITIES=scalar
        ZACC_MAJOR_BRANCH=scalar
        ZACC_SCALAR=1)

add_library(zacc.interface.sse.sse2 INTERFACE)
target_native_compile_options(zacc.interface.sse.sse2 INTERFACE -msse2)
target_compile_definitions(zacc.interface.sse.sse2 INTERFACE
        ZACC_CAPABILITIES=sse2
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

add_library(zacc.interface.sse.sse3 INTERFACE)
target_native_compile_options(zacc.interface.sse.sse3 INTERFACE -msse3 -mssse3)
target_compile_definitions(zacc.interface.sse.sse3 INTERFACE
        ZACC_CAPABILITIES=sse3
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

add_library(zacc.interface.sse.sse41 INTERFACE)
target_native_compile_options(zacc.interface.sse.sse41 INTERFACE -msse4.1)
target_compile_definitions(zacc.interface.sse.sse41 INTERFACE
        ZACC_CAPABILITIES=sse41
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

add_library(zacc.interface.sse.sse41.fma3 INTERFACE)
target_native_compile_options(zacc.interface.sse.sse41.fma3 INTERFACE -msse4.1 -mfma)
target_compile_definitions(zacc.interface.sse.sse41.fma3 INTERFACE
        ZACC_CAPABILITIES=sse41_fma3
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

add_library(zacc.interface.sse.sse41.fma4 INTERFACE)
target_native_compile_options(zacc.interface.sse.sse41.fma4 INTERFACE -msse4.1 -mfma4)
target_compile_definitions(zacc.interface.sse.sse41.fma4 INTERFACE
        ZACC_CAPABILITIES=sse41_fma4
        ZACC_MAJOR_BRANCH=sse
        ZACC_SSE=1)

add_library(zacc.interface.avx INTERFACE)
target_native_compile_options(zacc.interface.avx INTERFACE -mavx -mfma)
target_compile_definitions(zacc.interface.avx INTERFACE
        ZACC_CAPABILITIES=avx1
        ZACC_MAJOR_BRANCH=avx
        ZACC_AVX=1)

add_library(zacc.interface.avx2 INTERFACE)
target_native_compile_options(zacc.interface.avx2 INTERFACE -mavx2 -mfma)
target_compile_definitions(zacc.interface.avx2 INTERFACE
        ZACC_CAPABILITIES=avx2
        ZACC_MAJOR_BRANCH=avx2
        ZACC_AVX2=1)

add_library(zacc.interface.avx512 INTERFACE)
target_native_compile_options(zacc.interface.avx512 INTERFACE -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)
target_compile_definitions(zacc.interface.avx512 INTERFACE
        ZACC_CAPABILITIES=avx512
        ZACC_MAJOR_BRANCH=avx512
        ZACC_AVX512=1)

include(cmake/dispatched_build.cmake)

# BUILD! ===============================================================================================================

# fetch dependencies
add_subdirectory(dependencies)

# add codegen targets
include(codegen/CMakeLists.txt)

# add app targets
include(src/CMakeLists.txt)

# add test targets
include(test/CMakeLists.txt)

# add documentation targets
include(doc/CMakeLists.txt)