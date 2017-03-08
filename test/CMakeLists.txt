foreach(branch ${branches})
    get_branch_files(files ${branch} "${test.schema}")

    add_executable(zacc.${branch}.playground WIN32 ${CMAKE_CURRENT_LIST_DIR}/playground.cpp)
    add_dependencies("zacc.${branch}.playground" "zacc.generate.${branch}.types" )

    add_executable("zacc.${branch}.tests" ${files})
    add_dependencies("zacc.${branch}.tests" "zacc.generate.${branch}.types" "zacc.generate.${branch}.tests" )

    target_link_libraries("zacc.${branch}.tests" gtest_main)

    target_compile_options("zacc.${branch}.tests" PUBLIC ${branch_flags_${branch}})
    target_compile_options("zacc.${branch}.playground" PUBLIC ${branch_flags_${branch}})

    foreach(def ${branch_defs_${branch}})
        target_compile_definitions(zacc.${branch}.tests  PUBLIC "${def}")
        target_compile_definitions(zacc.${branch}.playground  PUBLIC "${def}")

        get_branch_files(inc ${branch} "types.hpp")
        string(REPLACE "include/" "" inc ${inc})

        target_compile_definitions(zacc.${branch}.tests  PUBLIC "ZACC_MAJOR_BRANCH_INC=\"${inc}\"")
        target_compile_definitions(zacc.${branch}.playground  PUBLIC "ZACC_MAJOR_BRANCH_INC=\"${inc}\"")
    endforeach()

    list(APPEND tests "zacc.${branch}.tests")
    list(APPEND playgrounds "zacc.${branch}.playground")
endforeach()

add_custom_target(zacc.tests.all DEPENDS ${tests})
add_custom_target(zacc.playgrounds.all DEPENDS ${tests})