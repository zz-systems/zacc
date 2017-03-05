foreach(branch ${branches})
    get_branch_files(files ${branch} "${test.schema}")

    add_executable("zacc.${branch}.tests" ${files})
    add_dependencies("zacc.${branch}.tests" "zacc.generate.${branch}.types" "zacc.generate.${branch}.tests" )

    target_link_libraries("zacc.${branch}.tests" gtest_main)

    target_compile_options("zacc.${branch}.tests" PUBLIC ${branch_flags_${branch}})

    foreach(def ${branch_defs_${branch}})
        target_compile_definitions(zacc.${branch}.tests  PUBLIC "${def}")

        get_branch_files(inc ${branch} "types.hpp")
        string(REPLACE "include/" "" inc ${inc})

        target_compile_definitions(zacc.${branch}.tests  PUBLIC "ZACC_MAJOR_BRANCH_INC=\"${inc}\"")
    endforeach()

    list(APPEND test ${test})
endforeach()

add_custom_target(zacc.tests.all DEPENDS ${tests})