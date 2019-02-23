cmake_minimum_required(VERSION 3.3.2)
project(zacc VERSION 1.0.0)

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cmake/zacc.shared.cmake)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

option(BUILD_TESTS "Build unit tests" OFF)
option(BUILD_EXAMPLES "Build examples" ON)

# include branched code generation config
add_subdirectory(codegen/backend)

# fetch dependencies
if(BUILD_EXAMPLES)
    include_directories(dependencies/CImg)
endif()

if(BUILD_TESTS)
    add_subdirectory(dependencies/googletest)
endif()

# add codegen targets
include(codegen/CMakeLists.txt)

# add app targets
include(src/CMakeLists.txt)

# add test targets
if(BUILD_TESTS)
    enable_testing()
    include(test/CMakeLists.txt)
endif()

# add example targets
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

add_library(zacc INTERFACE)
add_library(zacc::zacc ALIAS zacc)
target_include_directories(zacc INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS zacc EXPORT zacc)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/zacc")

set(CPACK_PACKAGE_DESCRIPTION "PROJECT_NAME")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "ZZ-SYSTEMS")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

include(CPack)