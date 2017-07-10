enable_testing()

set(ZACC_TEST_MAIN ${CMAKE_CURRENT_LIST_DIR}/test_main.cpp)
set(ZACC_TEST_ENTRYPOINT ${CMAKE_CURRENT_LIST_DIR}/test_entry_point.cpp)

file(GLOB test.traits "${CMAKE_CURRENT_LIST_DIR}/traits/*.cpp")
file(GLOB test.math "${CMAKE_CURRENT_LIST_DIR}/math/*.cpp")


if(BUILD_SANITIZE_MEMORY)
    add_compile_options(-fsanitize=address)
    link_libraries(-fsanitize=address)
endif()

zacc_add_dispatched_tests(zacc.tests
        TEST_MAIN ${ZACC_TEST_MAIN}
        TEST_ENTRYPOINT ${ZACC_TEST_ENTRYPOINT}
        BRANCHES "${branches}"
        INCLUDES ${CMAKE_SOURCE_DIR}/include
        SOURCES
            ${test.traits}
            ${test.math}
        )