cmake_minimum_required(VERSION 3.3.2)
project(zacc.examples)


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # requires XQuartz
    include_directories(AFTER "/usr/X11/include")
    link_directories("/usr/X11/lib" "/usr/X11R6/lib")
endif()

zacc_add_dispatched_executable(zacc_examples
        BRANCHES "${branches}"
        INCLUDES
            ${PROJECT_SOURCE_DIR}/include
        ENTRYPOINT
            ${PROJECT_SOURCE_DIR}/branch_entrypoint.cpp
        SOURCES
            ${PROJECT_SOURCE_DIR}/examples.cpp
        )


if(WIN32)
    #target_link_libraries(zacc_examples)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # requires XQuartz
    target_link_libraries(zacc_examples PUBLIC X11)
else()
    target_link_libraries(zacc_examples PUBLIC X11 jpeg png)
endif()
