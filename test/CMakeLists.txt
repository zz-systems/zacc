enable_testing()

foreach(branch ${branches})
    get_branch_files(files ${branch} "${test.schema}")

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
    endforeach()

        add_test(
                NAME ci.zacc.tests.${branch}
                COMMAND zacc.tests.${branch}
        )

    list(APPEND tests "zacc.tests.${branch}")
endforeach()

add_custom_target(zacc.tests.all DEPENDS ${tests})

set(GTEST_LIBS $<TARGET_FILE:gtest> $<TARGET_FILE:gtest_main>)
add_custom_command(TARGET zacc.tests.scalar POST_BUILD      
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  
        ${GTEST_LIBS}      
        $<TARGET_FILE_DIR:zacc.tests.scalar> 
		) 