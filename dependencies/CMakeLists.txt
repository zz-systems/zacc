cmake_minimum_required(VERSION 3.3.2)
project(zacc.dependencies NONE)


add_subdirectory(googletest)

add_library(cimg INTERFACE)
target_include_directories(cimg INTERFACE cimg)

if(NOT WIN32)
    find_package(X11 REQUIRED)

    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

    target_include_directories(cimg INTERFACE ${X11_INCLUDE_DIR})

    target_link_directories(cimg INTERFACE ${X11_LIBRARIES} "/usr/X11/lib" "/usr/X11R6/lib")
    target_link_libraries(cimg INTERFACE ${X11_LIBRARIES})

    if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        target_link_libraries(cimg INTERFACE jpeg png m pthread)
    endif()
endif()