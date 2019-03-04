cmake_minimum_required(VERSION 3.3.2)
project(zacc VERSION 0.5.0)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(GenerateExportHeader)

add_library(zacc INTERFACE)
add_library(zacc::zacc ALIAS zacc)
target_compile_definitions(zacc INTERFACE ZACC_FAST_FLOAT=0)
include(cmake/ZACC.cmake)

target_link_libraries(zacc INTERFACE zacc.compiler)

target_include_directories(zacc INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS zacc zacc.compiler zacc.compiler.gcc zacc.compiler.clang zacc.compiler.clangcl zacc.compiler.msvc zacc.compiler.icc
        zacc.arch.scalar
        zacc.arch.sse2 zacc.arch.sse3 zacc.arch.sse41 zacc.arch.sse41.fma3 zacc.arch.sse41.fma4
        zacc.arch.avx1 zacc.arch.avx1.fma3 zacc.arch.avx2 zacc.arch.avx512
        zacc.arch.opencl

    EXPORT zacc-export
    RUNTIME DESTINATION     ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION     ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION     ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION    ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT zacc-export
    FILE ZaccTargets.cmake
    NAMESPACE zacc:: 
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zacc)


write_basic_package_version_file(
    ZaccConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(cmake/ZACC.cmake ZACC.cmake COPYONLY)
configure_file(cmake/ZaccConfig.cmake.in ZaccConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ZaccConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/ZaccConfigVersion.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/ZACC.cmake"
        COMPONENT zacc-dev
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zacc
        )

add_library(zacc_dl SHARED src/dl.cpp)
add_library(zacc::zacc_dl ALIAS zacc_dl)

set_target_properties(zacc_dl PROPERTIES VERSION 1.0)
target_compile_definitions(zacc_dl PRIVATE zacc_dl_EXPORTS=1)
target_link_libraries(zacc_dl PRIVATE zacc)

generate_export_header(zacc_dl EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/zacc/zacc_dl_export.h)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/zacc/zacc_dl_export.h"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )


if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(zacc_dl PRIVATE -Wl,--no-as-needed -ldl)
endif()

install(TARGETS zacc_dl
        EXPORT  zacc_dl
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}")
        #PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

add_executable(zacc_cpuid WIN32 src/cpuid.cpp)
target_link_libraries(zacc_cpuid PRIVATE zacc)

install(TARGETS zacc_cpuid DESTINATION "${CMAKE_INSTALL_BINDIR}")


option(BUILD_TESTS "Build unit tests" OFF)
option(BUILD_EXAMPLES "Build examples" ON)

# fetch dependencies
if(BUILD_EXAMPLES)
    include_directories(dependencies/CImg)
endif()

# if(BUILD_TESTS)
#     add_subdirectory(dependencies/googletest)
# endif()

# add codegen targets
#include(codegen/CMakeLists.txt)

# add app targets
#include(src/CMakeLists.txt)

# add test targets
# if(BUILD_TESTS)
#     enable_testing()
#     add_subdirectory(test)
# endif()

# add example targets
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()