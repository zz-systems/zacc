
set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/zacc)

add_executable(platform_detector WIN32 ${CMAKE_SOURCE_DIR}/auxapps/platform_detector.cpp)