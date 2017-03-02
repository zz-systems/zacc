cmake_minimum_required(VERSION 3.6)
project(zacc)

set(CMAKE_CXX_STANDARD 14)

# Clang doesn't support the __float128 type. Here are some workarounds:
# https://bugs.llvm.org//show_bug.cgi?id=13530#c3
# 1) build with -D__STRICT_ANSI__
# 2) edit bits/c++config.h (somewhere inside /usr/include/c++/4.7.0) so it doesn't define _GLIBCXX_USE_FLOAT128
# 3) configure libstdc++ with clang instead of gcc
# 4) add 'struct __float128;' before you include any STL header
add_definitions(-D__STRICT_ANSI__)

include_directories(
        ${CMAKE_SOURCE_DIR}/zacc
        ${CMAKE_SOURCE_DIR})

include(cmake/util.cmake)
include(cmake/options.cmake)
include(cmake/globalsettings.cmake)
include(cmake/branches.cmake)
include(cmake/codegen.cmake)
include(cmake/docgen.cmake)

include(${CMAKE_SOURCE_DIR}/tests/tests.cmake)
include(${CMAKE_SOURCE_DIR}/auxapps/auxapps.cmake)

function(add_test_target target branch files)
    add_executable("zacc.${branch}.tests" ${files})
    target_link_libraries("zacc.${branch}.tests" gtest_main)

    add_dependencies("zacc.${branch}.tests" "zacc.generate.${branch}.types" "zacc.generate.${branch}.tests" )

    target_compile_options("zacc.${branch}.tests" PUBLIC ${compiler_flags_${branch}})

    set(${target} "zacc.${branch}.tests" PARENT_SCOPE)
endfunction()

foreach(branch ${branches})
    string(REPLACE "." ";" parts ${branch})
    list(LENGTH parts len)
    if(${len} EQUAL 2) # majorbranch.subbranch
        list(GET parts 0 majorbranch)

        find_files(templates "*/${majorbranch}/*${template.schema}")
        find_files(files "*/${majorbranch}/*${test.schema}")

    elseif(${len} EQUAL 1) # majorbranch
        find_files(templates "*/${branch}/*${template.schema}")
        find_files(files "*/${branch}/*${test.schema}")
    else()
        message(ERROR "malformed branch definition")
    endif()

    generate(${branch} "${templates}")

    add_test_target(test ${branch} "${files}")

    message("branch_defs: ${branch} - ${branch_defs_${branch}}")
    foreach(def ${branch_defs_${branch}})
        target_compile_definitions(zacc.${branch}.tests  PUBLIC "${def}=1")
    endforeach()

    list(APPEND tests ${test})
endforeach()

add_custom_target(zacc.generate.types.all DEPENDS ${generate.types.all})
add_custom_target(zacc.generate.tests.all DEPENDS ${generate.tests.all})
add_custom_target(zacc.generate.all DEPENDS zacc.generate.types.all zacc.generate.tests.all)
add_custom_target(zacc.tests.all DEPENDS ${tests})