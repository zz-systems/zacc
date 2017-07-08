function(add_dispatched_vectorized_target target_name)
    set(options OPTIONAL ZACC_FAST_FLOAT)
    set(oneValueArgs "")
    set(multiValueArgs INCLUDES ENTRYPOINTS SOURCES LIBRARIES BRANCHES)

    cmake_parse_arguments(add_dispatched_vectorized_target "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    #set(target_name ${add_dispatched_vectorized_target_TARGET})
    set(target_includes ${add_dispatched_vectorized_target_INCLUDES})
    set(target_entrypoints ${add_dispatched_vectorized_target_ENTRYPOINTS})
    set(target_sources ${add_dispatched_vectorized_target_SOURCES})
    set(target_branches ${add_dispatched_vectorized_target_BRANCHES})
    set(target_libraries ${add_dispatched_vectorized_target_LIBRARIES})

    foreach(branch ${target_branches})
        message(STATUS "Adding dispatched vectorized branch ${target_name}.${branch}")

        add_library("${target_name}.${branch}" STATIC ${target_entrypoints})
        target_link_libraries("${target_name}.${branch}" PRIVATE zacc.system zacc.interface.${branch})
        target_link_libraries("${target_name}.${branch}" PUBLIC gtest zacc.system zacc.interface.${branch}.defs)

        add_dependencies("${target_name}.${branch}" "zacc.generate.${branch}.types" "zacc.generate.${branch}.tests" )

        target_include_directories(${target_name}.${branch} PRIVATE ${target_includes})


        list(APPEND branch_objects ${target_name}.${branch})#$<TARGET_OBJECTS:${target_name}.${branch}>)
    endforeach()

    message(STATUS "Combining dispatched vectorized branches to ${target_name}")

    add_library(${target_name} SHARED  ${target_sources})
    target_link_libraries(${target_name} zacc.system ${branch_objects} ${target_libraries})
    target_compile_definitions(${target_name} PUBLIC ZACC_FAST_FLOAT=false)
endfunction()

function(add_branch_test target_name)
    set(options OPTIONAL ZACC_FAST_FLOAT)
    set(oneValueArgs "")
    set(multiValueArgs TESTMAIN INCLUDES SOURCES LIBRARIES BRANCHES DEPENDS)

    cmake_parse_arguments(add_branch_test "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    set(test_main ${add_branch_test_TESTMAIN})
    set(target_includes ${add_branch_test_INCLUDES})
    set(target_sources ${add_branch_test_SOURCES})
    set(target_dependencies ${add_branch_test_DEPENDS})
    set(target_branches ${add_branch_test_BRANCHES})
    set(target_libraries ${add_branch_test_LIBRARIES})

    message("test_main: ${test_main}")
    foreach(branch ${target_branches})
        message(STATUS "Adding dispatched test ${target_name}.${branch}")

        get_branch_files(files ${branch} "${test.schema}")

        add_library("${target_name}.${branch}.impl" SHARED ${files} ${target_sources})
        target_include_directories(${target_name}.${branch}.impl PUBLIC ${gtest_SOURCE_DIR}/include ${target_includes})
        target_compile_definitions(${target_name}.${branch}.impl PRIVATE ZACC_EXPORTS=1)
        target_link_libraries("${target_name}.${branch}.impl" PRIVATE gtest zacc.system zacc.interface.${branch})


        add_executable("${target_name}.${branch}" ${test_main})
        target_compile_definitions(${target_name}.${branch} PRIVATE ZACC_TEST_LIBNAME="$<TARGET_FILE_NAME:${target_name}.${branch}.impl>")
        target_link_libraries("${target_name}.${branch}" gtest zacc.system ${target_libraries} zacc.system zacc.system.loader zacc.interface.${branch}.defs)

        add_test(
                NAME ci.${target_name}.${branch}
                COMMAND ${target_name}.${branch}
        )

        set(GTEST_LIBS $<TARGET_FILE:gtest> $<TARGET_FILE:${target_name}.${branch}.impl>)


        add_custom_command(TARGET "${target_name}.${branch}" POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${GTEST_LIBS}
                $<TARGET_FILE_DIR:${target_name}.${branch}>
                )

        list(APPEND tests "${target_name}.${branch}")
    endforeach()

    add_custom_target(${target_name}.all DEPENDS ${tests})
endfunction()