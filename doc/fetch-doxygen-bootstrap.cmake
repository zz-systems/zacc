cmake_minimum_required(VERSION 2.8.2)

project(fetch-doxygen-bootstrap NONE)

include(ExternalProject)
ExternalProject_Add(doxygen-bootstrap
        GIT_REPOSITORY    https://github.com/StratifyLabs/Doxygen-Bootstrap.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_BINARY_DIR}/doxygen-bootstrap"
        BINARY_DIR        "${CMAKE_BINARY_DIR}/doxygen-bootstrap-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
        )