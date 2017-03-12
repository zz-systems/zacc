set(doc.deps
        "${codegen.ext}"
        "zacc.generate.types.all")

configure_file(doc/fetch-doxygen-bootstrap.cmake doxygen-bootstrap-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doxygen-bootstrap-download )
if(result)
    message(FATAL_ERROR "CMake step for doxygen-bootstrap failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doxygen-bootstrap-download )
if(result)
    message(FATAL_ERROR "Build step for doxygen-bootstrap failed: ${result}")
endif()


if(BUILD_DOCUMENTATION)

    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        file(GLOB doxygen-bootstrap-files "${CMAKE_CURRENT_BINARY_DIR}/doxygen-bootstrap/*.*")

        #file(COPY "${CMAKE_CURRENT_BINARY_DIR}/doxygen-bootstrap/doxy-boot.js" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/doc)
        #file(COPY "${CMAKE_CURRENT_BINARY_DIR}/doxygen-bootstrap/style.css" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/doc)

        file(COPY ${doxygen-bootstrap-files} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/doc)

        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.conf.in ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile.conf @ONLY)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/header.html ${CMAKE_CURRENT_BINARY_DIR}/doc/header.html COPYONLY)
        #configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/footer.html ${CMAKE_CURRENT_BINARY_DIR}/doc/footer.html COPYONLY)

        add_custom_target(zacc.documentation.doxygen #${doc_target_name}
                ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile.conf
                DEPENDS ${doc.deps}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc
                COMMENT "Generating API documentation with Doxygen" VERBATIM
                )

        #add_custom_target(zacc.documentation
        #        COMMAND sphinx-build -b html . sphinx/build/html
        #        WORKING_DIRECTORY doc
        #        DEPENDS zacc.documentation.doxygen
        #        COMMENT "Generating HTML API documentation"
        #        )
    endif(DOXYGEN_FOUND)
endif()