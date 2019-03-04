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

if(BUILD_SCALAR)
    set(branches ${branches} scalar)    

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_SCALAR=1)
endif()

if(BUILD_SSE)
    set(branches ${branches} sse2 sse3 sse41 sse41.fma3 sse41.fma4)

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_SSE=1)
endif()

if(BUILD_AVX)
    set(branches ${branches} avx1 avx1.fma3)

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_AVX=1)
endif()

if(BUILD_AVX2)
    set(branches ${branches} avx2)

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_AVX2=1)
endif()

if(BUILD_AVX512)
    set(branches ${branches} avx512)

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_AVX512=1)
endif()

if(BUILD_OPENCL)
    set(branches ${branches} opencl)

    target_compile_definitions(zacc.kernel.host INTERFACE ZACC_OPENCL=1)
endif()
# ------------------------------------------------------------------------------


function(add_kernel kernel_name)
    add_library(${kernel_name} INTERFACE)
    target_link_libraries(${kernel_name} INTERFACE zacc zacc.kernel.host zacc_dl)
    target_compile_definitions(${kernel_name} INTERFACE ZACC_DYLIBNAME="${CMAKE_SHARED_LIBRARY_PREFIX}${kernel_name}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    
    foreach(branch ${branches})
        add_library(${kernel_name}.${branch} SHARED ${ARGN})

        target_link_libraries(${kernel_name}.${branch} PRIVATE zacc zacc.arch.${branch})

        target_link_libraries(${kernel_name} INTERFACE ${kernel_name}.${branch})
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
        foreach(branch ${branches})
            install(TARGETS ${target}.${branch} ${install_args})
        endforeach()
    endforeach()
endfunction(install_kernel)

function(kernel_include_directories kernel_name)
    set(options SYSTEM BEFORE)
    set(multiValueArgs INTERFACE PUBLIC PRIVATE)
    cmake_parse_arguments(F "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(include_directories_args ${ARGN})
    foreach(branch ${branches})
        target_include_directories(${kernel_name}.${branch} ${include_directories_args})
    endforeach()
endfunction(kernel_include_directories)