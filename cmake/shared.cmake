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

option(BUILD_SANITIZE_MEMORY "Build with clang memory sanitizer" Off)

option(BUILD_OPENMP "Build with OpenMP support" Off)

# util =================================================================================================================

macro(insert_kv dict key)
    set("${dict}_${key}" ${ARGN})
endmacro()

function(preprocess_paths path type template)
    string(REGEX REPLACE "${template.schema}" "${${type}.schema}" outpath ${template})
    string(REPLACE "codegen/" "" outpath ${outpath})

    set(${path} "${outpath}" PARENT_SCOPE)
endfunction()

function(find_files files schema)
    file(GLOB_RECURSE _files RELATIVE ${PROJECT_SOURCE_DIR} ${schema})
    set(${files} ${_files} PARENT_SCOPE)
endfunction()

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

macro(clang_cl_passthtrough_flags)
endmacro()

# compiler config ======================================================================================================

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")

	

    if(MSVC)
        message("Using clang-cl")
        set(CLANG_CL 1)       
		
		set(CMAKE_CXX_EXTENSIONS OFF)

		if(CMAKE_GENERATOR MATCHES "Visual Studio")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /GX /wd4996")
		else()
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -std=c++14 -Xclang -Wno-missing-braces -Xclang -Wmissing-field-initializers -Xclang -Wno-deprecated-declarations")#	-Xclang -fsanitize=alignment")
		endif()

        if(BUILD_SANITIZE_MEMORY)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fsanitize=alignment")
        endif()
        add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
    else()
        message("Using clang")        

		set(CMAKE_CXX_STANDARD 14)
		set(CMAKE_CXX_STANDARD_REQUIRED on)
		set(CMAKE_CXX_EXTENSIONS OFF)

        if(BUILD_SANITIZE_MEMORY)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=alignment")
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

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED on)
    set(CMAKE_CXX_EXTENSIONS ON)

    # GCC fails to retain attributes while passing as template arg. hide warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-attributes")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    message("Using Intel C++")

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED on)
    set(CMAKE_CXX_EXTENSIONS ON)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message("Using Visual Studio C++")

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED on)
    set(CMAKE_CXX_EXTENSIONS ON)

	
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

if(ENABLE_TRACE)
    add_definitions(-DZACC_TRACE)
    message("Adding trace")
endif()

if(BUILD_FAST_FLOAT)
    add_definitions(-DZACC_FAST_FLOAT=true)
else()
    add_definitions(-DZACC_FAST_FLOAT=false)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC AND (NOT CLANG_CL))
	#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/branch_flags_msvc.cmake)
	insert_kv(branch_flags  scalar              /arch:IA32)
	insert_kv(branch_flags  sse.sse2            /arch:SSE2)
	insert_kv(branch_flags  sse.sse3            /arch:SSE2)

	insert_kv(branch_flags  sse.sse41           /arch:SSE2)
	insert_kv(branch_flags  sse.sse41.fma3      /arch:SSE2)
	insert_kv(branch_flags  sse.sse41.fma4      /arch:SSE2)

	#insert_kv(branch_flags  sse.sse42      -msse4.1 -msse4.2)
	#insert_kv(branch_flags  sse.sse42.fma3 -msse4.1 -msse4.2 -mfma)
	#insert_kv(branch_flags  sse.sse42.fma4 -msse4.1 -msse4.2 -mfma4)

	insert_kv(branch_flags  avx           /arch:AVX)
	insert_kv(branch_flags  avx2          /arch:AVX2)
	insert_kv(branch_flags  avx512        /arch:AVX512)
else()
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
endif()

insert_kv(branch_defs   scalar          ZACC_CAPABILITIES=scalar        ZACC_MAJOR_BRANCH=scalar    ZACC_SCALAR=1)
insert_kv(branch_defs   sse.sse2        ZACC_CAPABILITIES=sse2          ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)
insert_kv(branch_defs   sse.sse3        ZACC_CAPABILITIES=sse3          ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)

insert_kv(branch_defs  sse.sse41        ZACC_CAPABILITIES=sse41         ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)
insert_kv(branch_defs  sse.sse41.fma3   ZACC_CAPABILITIES=sse41_fma3    ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)
insert_kv(branch_defs  sse.sse41.fma4   ZACC_CAPABILITIES=sse41_fma4    ZACC_MAJOR_BRANCH=sse       ZACC_SSE=1)

insert_kv(branch_defs   avx             ZACC_CAPABILITIES=avx1          ZACC_MAJOR_BRANCH=avx       ZACC_AVX=1)
insert_kv(branch_defs   avx2            ZACC_CAPABILITIES=avx2          ZACC_MAJOR_BRANCH=avx2      ZACC_AVX2=1)
insert_kv(branch_defs   avx512          ZACC_CAPABILITIES=avx512        ZACC_MAJOR_BRANCH=avx512    ZACC_AVX512=1)

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
    list(APPEND branches avx)

    list(APPEND generic_build_defs ZACC_AVX=1)
endif()

if(BUILD_AVX2_BRANCH)
    list(APPEND branches avx2)

    list(APPEND generic_build_defs ZACC_AVX2=1)
endif()

if(BUILD_AVX512_BRANCH)
    list(APPEND branches avx512)

    list(APPEND generic_build_defs ZACC_AVX512=1)
endif()

if(BUILD_OPENCL_BRANCH)
    list(APPEND branches openCL)

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


# build