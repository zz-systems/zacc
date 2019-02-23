add_library(zacc_dl SHARED src/dlloader.cpp)
add_library(zacc::zacc_dl ALIAS zacc_dl)

set_target_properties(zacc_dl PROPERTIES VERSION 1.0)

generate_export_header(zacc_dl)
target_compile_definitions(zacc_dl PRIVATE zacc_dl_EXPORTS=1)
target_include_directories(zacc_dl PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(zacc_dl PRIVATE -Wl,--no-as-needed -ldl)
endif()

install(TARGETS zacc_dl
        EXPORT  zacc
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT dev)

add_executable(zacc_cpuid WIN32 src/platform_detector.cpp)

install(TARGETS zacc_cpuid DESTINATION bin)

set(SHARED_LIB_DUMMY ${CMAKE_CURRENT_LIST_DIR}/dllmain.cpp)