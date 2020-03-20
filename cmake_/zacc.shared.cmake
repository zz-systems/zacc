# options ==============================================================================================================

# branches =============================================================================================================

option(BUILD_SCALAR_BRANCH "Build the scalar branch" ON)
option(BUILD_SSE_BRANCH "Build the sse branch" ON)
option(BUILD_AVX_BRANCH "Build the avx branch" OFF)
option(BUILD_AVX2_BRANCH "Build the avx2 branch" ON)
option(BUILD_AVX512_BRANCH "Build the avx512 branch" OFF)
option(BUILD_OPENCL_BRANCH "Build the OpenCL branch" OFF)

# optimization =========================================================================================================

option(BUILD_FAST_FLOAT "Build with relaxed IEEE754 options. Faster and less precise" Off)
option(BUILD_AGGRESSIVE_OPTIMIZATION "Build with aggressive optimization" Off)
option(BUILD_OPENMP "Build with OpenMP support" Off)

# debug ================================================================================================================

option(BUILD_ENABLE_TRACE "Enable tracing (EXTREMELY SLOW!)" OFF)
option(BUILD_SANITIZE_MEMORY "Build with clang memory sanitizer" Off)
option(BUILD_SANITIZE_UNDEFINED "Build with clang undefined behavior sanitizer" Off)

# profiling ============================================================================================================

option(BUILD_ENABLE_INSTRUMENTATION "Enable instrumentation build")

# compiler config ======================================================================================================

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    if(MSVC)
        message("Using clang-cl")
        set(CLANG_CL 1)

        set(CMAKE_CXX_EXTENSIONS OFF)

        set( gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)

        if(CMAKE_GENERATOR MATCHES "Visual Studio")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /GX /wd4996")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -std=c++17 -Xclang -Wno-missing-braces -Xclang -Wmissing-field-initializers -Xclang -Wno-deprecated-declarations")#	-Xclang -fsanitize=alignment")
        endif()

        add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
    else()
        message("Using clang")

        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_STANDARD_REQUIRED on)
        set(CMAKE_CXX_EXTENSIONS OFF)

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

        if(BUILD_SANITIZE_MEMORY)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=alignment")
        endif()

        if(BUILD_SANITIZE_UNDEFINED)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
        endif()

        if(BUILD_ENABLE_INSTRUMENTATION)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate")
        endif()

        if(BUILD_AGGRESSIVE_OPTIMIZATION)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstrict-vtable-pointers -flto")# -ffast-math")
        endif()
    endif()

    # Clang doesn't support the __float128 type. Here are some workarounds:
    # https://bugs.llvm.org//show_bug.cgi?id=13530#c3
    # 1) build with -D__STRICT_ANSI__
    # 2) edit bits/c++config.h (somewhere inside /usr/include/c++/4.7.0) so it doesn't define _GLIBCXX_USE_FLOAT128
    # 3) configure libstdc++ with clang instead of gcc
    # 4) add 'struct __float128;' before you include any STL header
    add_definitions(-D__STRICT_ANSI__)

elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message("Using GCC")

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED on)
    set(CMAKE_CXX_EXTENSIONS ON)

    # GCC fails to retain attributes while passing as template arg. hide warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-attributes")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    message("Using Intel C++")

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED on)
    set(CMAKE_CXX_EXTENSIONS ON)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message("Using Visual Studio C++")

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED on)
    set(CMAKE_CXX_EXTENSIONS ON)


    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()


# config ===============================================================================================================

if(BUILD_ENABLE_TRACE)
    add_definitions(-DZACC_TRACE)
    message("Adding trace")
endif()

if(BUILD_FAST_FLOAT)
    add_definitions(-DZACC_FAST_FLOAT=true)
else()
    add_definitions(-DZACC_FAST_FLOAT=false)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# branch config ========================================================================================================

if(BUILD_SCALAR_BRANCH)
    list(APPEND branches scalar)

    list(APPEND generic_build_defs ZACC_SCALAR=1)
endif()

if(BUILD_SSE_BRANCH)
    list(APPEND branches sse.sse2)
    list(APPEND branches sse.sse3)
    list(APPEND branches sse.sse41)
    list(APPEND branches sse.sse41.fma3)
    list(APPEND branches sse.sse41.fma4)

    list(APPEND generic_build_defs ZACC_SSE=1)
endif()

if(BUILD_AVX_BRANCH)
    list(APPEND branches avx.avx1)
    list(APPEND branches avx.avx1.fma3)

    list(APPEND generic_build_defs ZACC_AVX=1)
endif()

if(BUILD_AVX2_BRANCH)
    list(APPEND branches avx.avx2)

    list(APPEND generic_build_defs ZACC_AVX2=1)
endif()

if(BUILD_AVX512_BRANCH)
    list(APPEND branches avx.avx512)

    list(APPEND generic_build_defs ZACC_AVX512=1)
endif()

if(BUILD_OPENCL_BRANCH)
    list(APPEND branches gpgpu.opencl)

    list(APPEND generic_build_defs ZACC_OPENCL=1)
endif()

# packages =============================================================================================================

# look for python
find_package(PythonInterp 3.3 REQUIRED)

if(PYTHONINTERP_FOUND)
    get_filename_component(PYTHON_DIR ${PYTHON_EXECUTABLE} DIRECTORY CACHE)
else()
    message(FATAL_ERROR "Python not found")
endif()

if(BUILD_OPENMP)
    find_package(OpenMP)
    if(OPENMP_FOUND)
        message("OPENMP FOUND")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
endif()

#find_package(GTest REQUIRED)
#include_directories(
#        ${GTEST_INCLUDE_DIRS}
#        ${GMOCK_INCLUDE_DIRS}
#)


# build helpers ========================================================================================================
include (GenerateExportHeader)

function(add_kernel kernel_name)
    add_library(${kernel_name} INTERFACE)
    target_link_libraries(${kernel_name} INTERFACE zacc_dl)
    target_compile_definitions(${kernel_name} INTERFACE ZACC_DYLIBNAME="${CMAKE_SHARED_LIBRARY_PREFIX}${kernel_name}${CMAKE_SHARED_LIBRARY_SUFFIX}")

    foreach(branch ${branches})
        add_library(${kernel_name}.${branch} SHARED ${SHARED_LIB_DUMMY} ${ARGN})

        target_link_libraries(${kernel_name}.${branch}
            PRIVATE zacc.dispatch.${branch} 
            PUBLIC  zacc.dispatch.${branch}.dynamic)

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
endfunction()

function(zacc_add_dispatched_tests target_name)
    set(options OPTIONAL ZACC_FAST_FLOAT)
    set(oneValueArgs "")
    set(multiValueArgs TEST_MAIN TEST_ENTRYPOINT INCLUDES SOURCES LIBRARIES BRANCHES DEPENDS)

    cmake_parse_arguments(add_branch_test "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    set(test_main ${add_branch_test_TEST_MAIN})
    set(test_entrypoint ${add_branch_test_TEST_ENTRYPOINT})
    set(target_includes ${add_branch_test_INCLUDES})
    set(target_sources ${add_branch_test_SOURCES})
    set(target_dependencies ${add_branch_test_DEPENDS})
    set(target_branches ${add_branch_test_BRANCHES})
    set(target_libraries ${add_branch_test_LIBRARIES})

    string(REPLACE "." "_" macro_target_name "${macro_target_name}")
    string(TOUPPER ${target_name} macro_target_name)

    foreach(branch ${target_branches})
        message(STATUS "Adding dispatched test ${target_name}.${branch}")

        get_arch_files(files ${branch} "${test.schema}")
        message(STATUS "branch files: ${files}")
        add_library("${target_name}.${branch}.impl" SHARED ${files} ${target_sources} ${test_entrypoint})
        target_include_directories(${target_name}.${branch}.impl PUBLIC ${gtest_SOURCE_DIR}/include ${target_includes})

        generate_export_header(${target_name}.${branch}.impl
                BASE_NAME ${target_name}
                EXPORT_MACRO_NAME ${macro_target_name}_BRANCH_EXPORT
                EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${target_name}_branch_export.hpp
                STATIC_DEFINE ${macro_target_name}_BRANCH_BUILT_AS_STATIC
                )

        target_link_libraries("${target_name}.${branch}.impl" 
            PRIVATE gtest zacc.dispatch.${branch} 
            PUBLIC zacc.dispatch.${branch}.dynamic)

        add_executable("${target_name}.${branch}" ${test_main})

        target_compile_definitions(${target_name}.${branch} PRIVATE ZACC_DYLIBNAME="${search_prefix}$<TARGET_FILE_NAME:${target_name}.${branch}.impl>")

        target_link_libraries("${target_name}.${branch}" ${target_libraries} zacc_dl zacc.dispatch.${branch}.static)
        add_dependencies("${target_name}.${branch}" "${target_name}.${branch}.impl")

        add_test(
                NAME ci.${target_name}.${branch}
                COMMAND $<TARGET_FILE:${target_name}.${branch}>
        )

        list(APPEND tests "${target_name}.${branch}")
    endforeach()

    add_custom_target(${target_name}.all DEPENDS ${tests})
endfunction()
