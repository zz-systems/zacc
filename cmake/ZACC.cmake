# --- Compiler settings --------------------------------------------------------
add_library(zacc.compiler INTERFACE)

# set_target_properties(zacc.compiler PROPERTIES
#     CXX_STANDARD 14
#     CXX_STANDARD_REQUIRED YES
#     CXX_EXTENSIONS NO
# )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(zacc.compiler.gcc INTERFACE)
add_library(zacc.compiler.clang INTERFACE)
add_library(zacc.compiler.clangcl INTERFACE)
add_library(zacc.compiler.msvc INTERFACE)
add_library(zacc.compiler.icc INTERFACE)

target_compile_options(zacc.compiler.gcc 
    INTERFACE 
        # GCC fails to retain attributes while passing as template arg. hide warnings
        -Wno-ignored-attributes) 

target_compile_options(zacc.compiler.clang 
    INTERFACE 
        -Wall 
        -Wextra
        # Clang doesn't support the __float128 type.
        -D__STRICT_ANSI__)

target_compile_options(zacc.compiler.clangcl 
    INTERFACE 
        -Xclang -std=c++14 
        -Xclang -Wno-missing-braces 
        -Xclang -Wmissing-field-initializers 
        -Xclang -Wno-deprecated-declarations 
        -DNOMINMAX 
        # MSVC has minmax macro pollution
        -D_USE_MATH_DEFINES
        # Clang doesn't support the __float128 type.
        -D__STRICT_ANSI__)

target_compile_options(zacc.compiler.icc 
    INTERFACE)

target_compile_options(zacc.compiler.msvc 
    INTERFACE 
        # MSVC has minmax macro pollution
        -DNOMINMAX         
        -D_USE_MATH_DEFINES)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(MSVC)
        message(STATUS "Using clang-cl.")
        target_link_libraries(zacc.compiler INTERFACE zacc.compiler.clangcl)
    else()
        message(STATUS "Using clang.")
        target_link_libraries(zacc.compiler INTERFACE zacc.compiler.clang)
    endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Using GCC.")
    target_link_libraries(zacc.compiler INTERFACE zacc.compiler.gcc)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    message(WARNING "ICC not tested.")
    target_link_libraries(zacc.compiler INTERFACE zacc.compiler.icc)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message(FATAL_ERROR "MSVC not supported!")
    target_link_libraries(zacc.compiler INTERFACE zacc.compiler.msvc)
endif()
# ------------------------------------------------------------------------------

# --- Architectures ------------------------------------------------------------
add_library(zacc.arch.scalar INTERFACE)
target_compile_definitions(zacc.arch.scalar INTERFACE ZACC_MAJOR_ARCH=scalar -DZACC_SCALAR=1 ZACC_ARCH=scalar)

add_library(zacc.arch.sse2 INTERFACE)
add_library(zacc.arch.sse3 INTERFACE)
add_library(zacc.arch.sse41 INTERFACE)
add_library(zacc.arch.sse41.fma3 INTERFACE)
add_library(zacc.arch.sse41.fma4 INTERFACE)

target_compile_definitions(zacc.arch.sse2       INTERFACE ZACC_MAJOR_ARCH=sse ZACC_SSE=1 ZACC_ARCH=sse2        )
target_compile_definitions(zacc.arch.sse3       INTERFACE ZACC_MAJOR_ARCH=sse ZACC_SSE=1 ZACC_ARCH=sse3        )
target_compile_definitions(zacc.arch.sse41      INTERFACE ZACC_MAJOR_ARCH=sse ZACC_SSE=1 ZACC_ARCH=sse41       )
target_compile_definitions(zacc.arch.sse41.fma3 INTERFACE ZACC_MAJOR_ARCH=sse ZACC_SSE=1 ZACC_ARCH=sse41_fma3  )
target_compile_definitions(zacc.arch.sse41.fma4 INTERFACE ZACC_MAJOR_ARCH=sse ZACC_SSE=1 ZACC_ARCH=sse41_fma4  )

target_compile_options(zacc.arch.sse2       INTERFACE -msse2)
target_compile_options(zacc.arch.sse3       INTERFACE -msse2 -msse3 -mssse3)
target_compile_options(zacc.arch.sse41      INTERFACE -msse2 -msse3 -mssse3 -msse4.1)
target_compile_options(zacc.arch.sse41.fma3 INTERFACE -msse2 -msse3 -mssse3 -msse4.1 -mfma)
target_compile_options(zacc.arch.sse41.fma4 INTERFACE -msse2 -msse3 -mssse3 -msse4.1 -mfma4)


add_library(zacc.arch.avx1 INTERFACE)
add_library(zacc.arch.avx1.fma3 INTERFACE)
add_library(zacc.arch.avx2 INTERFACE)
add_library(zacc.arch.avx512 INTERFACE)

target_compile_definitions(zacc.arch.avx1       INTERFACE ZACC_MAJOR_ARCH=avx       ZACC_AVX=1      ZACC_ARCH=avx1      )
target_compile_definitions(zacc.arch.avx1.fma3  INTERFACE ZACC_MAJOR_ARCH=avx       ZACC_AVX=1      ZACC_ARCH=avx1_fma3 )
target_compile_definitions(zacc.arch.avx2       INTERFACE ZACC_MAJOR_ARCH=avx2      ZACC_AVX2=1     ZACC_ARCH=avx2      )
target_compile_definitions(zacc.arch.avx512     INTERFACE ZACC_MAJOR_ARCH=avx512    ZACC_AVX512=1   ZACC_ARCH=avx512    )

target_compile_options(zacc.arch.avx1       INTERFACE -mavx)
target_compile_options(zacc.arch.avx1.fma3  INTERFACE -mavx -mfma)
target_compile_options(zacc.arch.avx2       INTERFACE -mavx -mavx2 -mfma)
target_compile_options(zacc.arch.avx512     INTERFACE -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)


target_compile_definitions(zacc.arch.avx512
    INTERFACE ZACC_MAJOR_ARCH=avx512 ZACC_AVX512=1)

add_library(zacc.arch.opencl INTERFACE)
target_compile_definitions(zacc.arch.opencl     INTERFACE ZACC_MAJOR_ARCH=opencl ZACC_OPENCL=1 ZACC_ARCH=opencl)

# ------------------------------------------------------------------------------

option(BUILD_SCALAR "Build the scalar branch" ON)
option(BUILD_SSE "Build the sse branch" ON)
option(BUILD_AVX "Build the avx branch" OFF)
option(BUILD_AVX2 "Build the avx2 branch" ON)
option(BUILD_AVX512 "Build the avx512 branch" OFF)
option(BUILD_OPENCL "Build the OpenCL branch" OFF)

# --- Kernel Matrix ------------------------------------------------------------

add_library(zacc.kernel.host INTERFACE)

set(architectures "")
set(feature_groups "")
set(features "")

if(BUILD_SCALAR)
    list(APPEND architectures   scalar)
    list(APPEND feature_groups  DEFAULT)
    list(APPEND features        DEFAULT scalar)

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_SCALAR=1)
endif()

if(BUILD_SSE)
    list(APPEND architectures   sse2 sse3 sse41 sse41.fma3 sse41.fma4)
    list(APPEND feature_groups  SSE)
    list(APPEND features        SSE sse2 sse3 ssse3 sse41 sse42 fma3 fma4)

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_SSE=1)
endif()

if(BUILD_AVX)
    list(APPEND architectures   avx1 avx1.fma3)
    list(APPEND feature_groups  AVX1)
    list(APPEND features        AVX1 avx1 fma3)

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_AVX=1)
endif()

if(BUILD_AVX2)
    list(APPEND architectures   avx2)
    list(APPEND feature_groups  AVX2)
    list(APPEND features        AVX2 avx2 fma3)


    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_AVX2=1)
endif()

if(BUILD_AVX512)
    list(APPEND architectures   avx512)
    list(APPEND feature_groups  AVX512)
    list(APPEND features        AVX512 avx512)

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_AVX512=1)
endif()

if(BUILD_OPENCL)
    list(APPEND architectures   opencl)
    list(APPEND feature_groups  GPGPU)
    #list(APPEND features       GPGPU opencl)



    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_OPENCL=1)
endif()
# ------------------------------------------------------------------------------

function(add_permuted_tests target_name)
    set(multiValueArgs DEFAULT SSE AVX1 AVX2 AVX512 GPGPU)
    cmake_parse_arguments(F "${options}" "${oneValueArgs}" "${multiValueArgs}" ${features})

    foreach(group ${feature_groups})
        set(test_suffix "")
        set(test_features "")

        foreach(feature ${F_${group}})
            set(test_suffix "${test_suffix}.${feature}")
            list(APPEND test_features "--m${feature}")

            add_test(
                NAME ${target_name}${test_suffix}
                COMMAND $<TARGET_FILE:${target_name}> --mask=0 ${test_features}
            )
        endforeach()
    endforeach()
endfunction(add_permuted_tests)

function(add_kernel kernel_name)
    set(options LINK NOLINK)
    cmake_parse_arguments(F "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_library(${kernel_name} INTERFACE)
    target_link_libraries(${kernel_name} INTERFACE zacc zacc.kernel.host zacc_dl)
    target_compile_definitions(${kernel_name} INTERFACE ZACC_DYLIBNAME="${CMAKE_SHARED_LIBRARY_PREFIX}${kernel_name}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    
    foreach(architecture ${architectures})
        add_library(${kernel_name}.${architecture} SHARED ${F_UNPARSED_ARGUMENTS})

        target_link_libraries(${kernel_name}.${architecture} PRIVATE zacc zacc.arch.${architecture})

        add_dependencies(${kernel_name} INTERFACE ${kernel_name}.${architecture})

        if(F_LINK OR (NOT F_NOLINK))
            target_link_libraries(${kernel_name} INTERFACE ${kernel_name}.${architecture})
        endif()
    endforeach()
endfunction(add_kernel)


function(install_kernel)    
    set(multiValueArgs TARGETS EXPORT ARCHIVE LIBRARY RUNTIME FRAMEWORK BUNDLE PRIVATE_HEADER PUBLIC_HEADER RESOURCE INCLUDES)
    cmake_parse_arguments(F "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(install_args ${ARGN})
    foreach(p o ${F_TARGETS})
        list(REMOVE_AT install_args 0)
    endforeach()
    
    foreach(target ${F_TARGETS})
        foreach(architecture ${architectures})
            install(TARGETS ${target}.${architecture} ${install_args})
        endforeach()
    endforeach()
endfunction(install_kernel)

function(kernel_include_directories kernel_name)
    set(options SYSTEM BEFORE)
    set(multiValueArgs INTERFACE PUBLIC PRIVATE)
    cmake_parse_arguments(F "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(include_directories_args ${ARGN})
    foreach(architecture ${architectures})
        target_include_directories(${kernel_name}.${architecture} ${include_directories_args})
    endforeach()
endfunction(kernel_include_directories)

function(kernel_link_libraries kernel_name)
    set(oneValueArgs debug optimized general)
    set(multiValueArgs INTERFACE PUBLIC PRIVATE)
    cmake_parse_arguments(F "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(link_libraries_args ${ARGN})
    foreach(architecture ${architectures})
        target_link_libraries(${kernel_name}.${architecture} ${link_libraries_args})
    endforeach()
endfunction(kernel_link_libraries)