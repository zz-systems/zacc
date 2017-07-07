add_library(zacc.system STATIC
        "${CMAKE_CURRENT_LIST_DIR}/all.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/cpuid.cpp")

add_library(zacc.runtimeloader STATIC
        "${CMAKE_CURRENT_LIST_DIR}/runtime_loader.cpp")

add_executable(zacc.system.detect WIN32
        "${CMAKE_CURRENT_LIST_DIR}/platform_detector.cpp"
        )


target_link_libraries(zacc.system.detect zacc.system)