add_library(zacc.system.info STATIC
        "${CMAKE_CURRENT_LIST_DIR}/platform.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/cpuid.cpp")

add_library(zacc.system.loader SHARED
        "${CMAKE_CURRENT_LIST_DIR}/runtime_loader.cpp")

generate_export_header(zacc.system.loader
        BASE_NAME zacc.system.loader
        EXPORT_MACRO_NAME ZACC_LOADER_EXPORT
        EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/zacc_systemloader_export.hpp
        STATIC_DEFINE ZACC_LOADER_BUILT_AS_STATIC
        )

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "ADD libdl, GNU")
    link_libraries(zacc.system.loader -Wl,--no-as-needed -ldl)
elseif ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") AND (NOT APPLE) AND (NOT MSVC))
    message(STATUS "ADD libdl, Clang")
    link_libraries(zacc.system.loader -Wl,--no-as-needed -ldl)
else()
    message(STATUS "SKIP libdl")
endif()

target_compile_definitions(zacc.system.loader PRIVATE ZACC_EXPORTS=1)

add_executable(zacc.system.detect WIN32
        "${CMAKE_CURRENT_LIST_DIR}/platform_detector.cpp"
        )


target_link_libraries(zacc.system.detect zacc.system.info)

set(SHARED_LIB_DUMMY ${CMAKE_CURRENT_LIST_DIR}/dllmain.cpp)