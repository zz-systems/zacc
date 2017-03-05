add_library(zacc.system SHARED
        "${CMAKE_CURRENT_LIST_DIR}/platform.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/cpuid.cpp")

add_executable(zacc.system.detect WIN32
        "${CMAKE_CURRENT_LIST_DIR}/platform_detector.cpp"
        )

target_link_libraries(zacc.system.detect zacc.system)