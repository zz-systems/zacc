set(doc.deps
        "${codegen.ext}"
        "zacc.generate.types.all")

if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.conf.in ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile.conf @ONLY)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/conf.py ${CMAKE_CURRENT_BINARY_DIR}/doc/conf.py COPYONLY)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/contents.rst ${CMAKE_CURRENT_BINARY_DIR}/doc/contents.rst COPYONLY)

        add_custom_target(zacc.documentation.doxygen #${doc_target_name}
                ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.conf
                DEPENDS ${doc.deps}
                #WORKING_DIRECTORY doc
                COMMENT "Generating API documentation with Doxygen" VERBATIM
                )

        add_custom_target(zacc.documentation
                COMMAND sphinx-build -b html . sphinx/build/html
                WORKING_DIRECTORY doc
                DEPENDS zacc.documentation.doxygen
                COMMENT "Generating HTML API documentation"
                )
    endif(DOXYGEN_FOUND)
endif()