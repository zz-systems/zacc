enable_testing()

file(GLOB test.core "casting.cpp")
file(GLOB test.traits "traits/*.cpp")
file(GLOB test.math "math/*.cpp")
file(GLOB_RECURSE test.util "util/*.cpp")

set(testsources 
    ${test.core}
    ${test.traits}
    ${test.math}
    ${test.util}
)

#
#if(BUILD_SANITIZE_MEMORY)
#    add_compile_options(-fsanitize=address)
#    link_libraries(-fsanitize=address)
#endif()

# zacc_add_dispatched_tests(zacc.tests
#         TEST_MAIN ${ZACC_TEST_MAIN}
#         TEST_ENTRYPOINT ${ZACC_TEST_ENTRYPOINT}
#         BRANCHES "${branches}"
#         INCLUDES ${CMAKE_SOURCE_DIR}/include
#         SOURCES
#             ${test.core}
#             ${test.traits}
#             ${test.math}
#             ${test.util}

#             #"${CMAKE_CURRENT_LIST_DIR}/traits/conditional.cpp"
#         )


add_custom_target(zacc.tests)

add_kernel(test_kernel test_entry_point.cpp ${testsources})

foreach(branch ${branches})    
    add_executable(zacc.tests.${branch} test_main.cpp)
    target_link_libraries(zacc.tests.${branch} PRIVATE test_kernel)

    add_dependencies(zacc.tests zacc.tests.${branch})
    
    add_test(
                NAME zacc.tests.${branch}
                COMMAND $<TARGET_FILE:zacc.tests.${branch}>
            )
endforeach()