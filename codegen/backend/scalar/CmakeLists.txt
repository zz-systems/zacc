# x87 interface ========================================================================================================
add_library(zacc.interface.scalar INTERFACE)
add_library(zacc.interface.scalar.defs INTERFACE)

target_compile_definitions(zacc.interface.scalar.defs INTERFACE
        ZACC_CAPABILITIES=scalar
        ZACC_MAJOR_BRANCH=scalar
        ZACC_SCALAR=1)

target_link_libraries(zacc.interface.scalar INTERFACE zacc.interface.scalar.defs)