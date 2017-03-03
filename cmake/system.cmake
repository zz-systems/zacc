set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/zacc)

add_library(zacc.system
        ${CMAKE_SOURCE_DIR}/system/platform.cpp
        ${CMAKE_SOURCE_DIR}/system/cpuid.cpp)