enable_testing()

set(test_entrypoint ${CMAKE_CURRENT_LIST_DIR}/../src/test_entry_point.cpp)
set(test_main ${CMAKE_CURRENT_LIST_DIR}/../src/test_main.cpp)

file(GLOB test.traits "${CMAKE_CURRENT_LIST_DIR}/traits/*.cpp")
file(GLOB test.math "${CMAKE_CURRENT_LIST_DIR}/math/*.cpp")

add_branch_test(zacc.tests
        TESTMAIN ${test_main}
        BRANCHES "${branches}"
        INCLUDES ${CMAKE_SOURCE_DIR}/include
        SOURCES
            ${test_entrypoint}
            ${test.traits}
            ${test.math}
        LIBRARIES gtest zacc.system
        )