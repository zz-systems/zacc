cmake_minimum_required(VERSION 3.3.2)
project(examples.perlin)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)


include(ExternalProject)

ExternalProject_Add (
        zacc
        GIT_REPOSITORY "https://github.com/zz-systems/zacc.git"
        GIT_TAG "develop"
        UPDATE_COMMAND ""
        INSTALL_COMMAND "" )