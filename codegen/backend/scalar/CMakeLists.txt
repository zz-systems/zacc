# x87 interface ========================================================================================================
add_library(zacc.interface.scalar INTERFACE)
add_library(zacc.interface.scalar.defs INTERFACE)
target_compile_definitions(zacc.interface.scalar INTERFACE
        ZACC_MAJOR_BRANCH=scalar)

target_compile_definitions(zacc.interface.scalar.defs INTERFACE
        ZACC_CAPABILITIES=scalar
        ZACC_SCALAR=1)

target_link_libraries(zacc.interface.scalar INTERFACE zacc.interface.scalar.defs zacc.interface.codegen)