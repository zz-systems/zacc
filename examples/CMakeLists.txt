cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples)


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # requires XQuartz
    include_directories(AFTER "/usr/X11/include")
    link_directories("/usr/X11/lib" "/usr/X11R6/lib")
endif()

zacc_add_dispatched_executable(zacc.examples
        BRANCHES "${branches}"
        INCLUDES
            ${PROJECT_SOURCE_DIR}/include
        KERNELS
            ${PROJECT_SOURCE_DIR}/kernels.cpp
        SOURCES
            ${PROJECT_SOURCE_DIR}/examples.cpp
        )


if(WIN32)
    #target_link_libraries(zacc_examples)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # requires XQuartz
    target_link_libraries(zacc.examples PUBLIC X11)
else()
    target_link_libraries(zacc.examples PUBLIC X11 jpeg png m pthread)
endif()



#cmake_minimum_required(VERSION 3.3.2)
#project(examples.perlin)
#
#
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#
#include_directories(include)
#
#
#include(ExternalProject)
#
#ExternalProject_Add (
#        zacc
#        GIT_REPOSITORY "https://github.com/zz-systems/zacc.git"
#        GIT_TAG "develop"
#        UPDATE_COMMAND ""
#        INSTALL_COMMAND "" )