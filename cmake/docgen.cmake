cmake_minimum_required(VERSION 3.6)

if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(doc/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

        configure_file(doc/header.html                              ${CMAKE_CURRENT_BINARY_DIR}/header.html @ONLY)
        configure_file(doc/footer.html                              ${CMAKE_CURRENT_BINARY_DIR}/footer.html @ONLY)
        configure_file(doc/doxy-boot.js ${CMAKE_CURRENT_BINARY_DIR}/doxy-boot.js @ONLY)
        configure_file(doc/customdoxygen.css ${CMAKE_CURRENT_BINARY_DIR}/customdoxygen.css @ONLY)

        add_custom_target(gorynych_doc#${doc_target_name}
                ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen" VERBATIM
                )
    endif(DOXYGEN_FOUND)
endif()