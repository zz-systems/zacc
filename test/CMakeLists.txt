enable_testing()

set(test_main ${CMAKE_CURRENT_LIST_DIR}/../src/test_main.cpp)

set(GTEST_LIBS $<TARGET_FILE:gtest>)

add_branch_main(zacc.tests.test_main
        BRANCHES "${branches}"
        INCLUDES ${CMAKE_SOURCE_DIR}/include
        SOURCES ${test_main}
        LIBRARIES gtest zacc.system)

add_branch_test(zacc.tests
        BRANCHES "${branches}"
        INCLUDES ${CMAKE_SOURCE_DIR}/include
        SOURCES ${CMAKE_CURRENT_LIST_DIR}/test_trigonometry.cpp ${CMAKE_CURRENT_LIST_DIR}/test_matrix.cpp
        LIBRARIES gtest zacc.system
        )