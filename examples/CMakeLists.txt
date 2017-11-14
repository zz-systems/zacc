cmake_minimum_required(VERSION 3.3.2)


#zacc_add_dispatched_library(zacc.examples.impl
#        BRANCHES "${branches}"
#        INCLUDES
#            ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/dependencies/zacc/include
#        ENTRYPOINT
#            ${CMAKE_SOURCE_DIR}/src/cacophony_branch_entrypoint.cpp
#        SOURCES
#            ${CMAKE_SOURCE_DIR}/examples/examples.cpp
#            ${CMAKE_SOURCE_DIR}/src/dllmain.cpp
#        )
#
#add_executable(zacc.examples zacc_examples.cpp)
#
#if(WIN32)
#    target_link_libraries(zacc.examples cacophony)
#elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # requires XQuartz
#    target_link_libraries(zacc.examples X11 cacophony)
#else()
#    target_link_libraries(zacc.examples X11 jpeg png cacophony)
#endif()
