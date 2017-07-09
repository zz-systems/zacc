# x87 interface ========================================================================================================
add_library(zacc.interface.scalar INTERFACE)

add_library(zacc.interface.scalar.defs INTERFACE)
target_compile_definitions(zacc.interface.scalar.defs INTERFACE
        ZACC_MAJOR_BRANCH=scalar
        ZACC_CAPABILITIES=scalar)

add_library(zacc.interface.scalar.aggregate INTERFACE)
target_compile_definitions(zacc.interface.scalar.aggregate INTERFACE
        ZACC_SCALAR=1)

target_link_libraries(zacc.interface.scalar INTERFACE zacc.interface.scalar.aggregate zacc.interface.scalar.defs zacc.interface.codegen)