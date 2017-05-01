cmake_minimum_required(VERSION 2.8.2)

project(fetch_asyncplusplus NONE)

include(ExternalProject)
ExternalProject_Add(asyncplusplus
        GIT_REPOSITORY    		https://github.com/Amanieu/asyncplusplus.git
        GIT_TAG           		master
        SOURCE_DIR        		"${CMAKE_CURRENT_BINARY_DIR}/asyncplusplus/src"
        BINARY_DIR        		"${CMAKE_CURRENT_BINARY_DIR}/asyncplusplus/build"

        CONFIGURE_COMMAND 		""
        BUILD_COMMAND     		""
        INSTALL_COMMAND   		""
        TEST_COMMAND      		""
        )