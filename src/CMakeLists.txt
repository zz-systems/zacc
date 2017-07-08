add_library(zacc.system STATIC
        "${CMAKE_CURRENT_LIST_DIR}/all.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/cpuid.cpp")

add_library(zacc.system.loader SHARED
        "${CMAKE_CURRENT_LIST_DIR}/runtime_loader.cpp")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    link_libraries(zacc.system.loader -Wl,--no-as-needed -ldl)
endif()

target_compile_definitions(zacc.system.loader PRIVATE ZACC_EXPORTS=1)

add_executable(zacc.system.detect WIN32
        "${CMAKE_CURRENT_LIST_DIR}/platform_detector.cpp"
        )


target_link_libraries(zacc.system.detect zacc.system)