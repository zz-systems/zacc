enable_testing()

foreach(branch ${branches})
    get_branch_files(files ${branch} "${test.schema}")

    #add_executable(zacc.${branch}.playground WIN32 ${CMAKE_CURRENT_LIST_DIR}/playground.cpp)
    #add_dependencies("zacc.${branch}.playground" "zacc.generate.${branch}.types" )
    #target_compile_options("zacc.${branch}.playground" PUBLIC ${branch_flags_${branch}})
    #target_include_directories(zacc.${branch}.playground PUBLIC "${CMAKE_SOURCE_DIR}/include")

    add_executable("zacc.tests.${branch}" ${files} ${CMAKE_CURRENT_LIST_DIR}/test_trigonometry.cpp ${CMAKE_CURRENT_LIST_DIR}/test_matrix.cpp)
    add_dependencies("zacc.tests.${branch}" "zacc.generate.${branch}.types" "zacc.generate.${branch}.tests" )

    target_link_libraries("zacc.tests.${branch}" gtest_main zacc.system)

	foreach(flag ${branch_flags_${branch}})
		if(CLANG_CL)
			set(flag "-Xclang ${flag}")
		endif()
		
		target_compile_options("zacc.tests.${branch}" PUBLIC ${branch_flags_${branch}})
	endforeach()
    target_include_directories(zacc.tests.${branch} PUBLIC "${CMAKE_SOURCE_DIR}/include")

    foreach(def ${branch_defs_${branch}})
        target_compile_definitions(zacc.tests.${branch}  PUBLIC "${def}")
        #target_compile_definitions(zacc.${branch}.playground  PUBLIC "${def}")
    endforeach()

        add_test(
                NAME ci.zacc.tests.${branch}
                COMMAND zacc.tests.${branch}
        )

    list(APPEND tests "zacc.tests.${branch}")
    #list(APPEND playgrounds "zacc.${branch}.playground")
endforeach()

add_custom_target(zacc.tests.all DEPENDS ${tests})
#add_custom_target(zacc.playgrounds.all DEPENDS ${tests})