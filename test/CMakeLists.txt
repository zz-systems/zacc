
foreach(branch ${branches})
    get_branch_files(files ${branch} "${test.schema}")

    message(STATUS "files: ${files}")
    add_executable("zacc.${branch}.tests" ${files})
    add_dependencies("zacc.${branch}.tests" "zacc.generate.${branch}.types" "zacc.generate.${branch}.tests" )

    target_link_libraries("zacc.${branch}.tests" gtest_main)
    target_compile_options("zacc.${branch}.tests" PUBLIC ${compiler_flags_${branch}})

    foreach(def ${branch_defs_${branch}})
        target_compile_definitions(zacc.${branch}.tests  PUBLIC "${def}=1")
    endforeach()

    list(APPEND test ${test})
endforeach()

add_custom_target(zacc.tests.all DEPENDS ${tests})