set(doc.deps
        "${codegen.ext}"
        "zacc.codegen")

find_package(Doxygen)
find_package(Sphinx)

if((DOXYGEN_FOUND) AND (SPHINX_FOUND))

    if(NOT DEFINED SPHINX_THEME)
        set(SPHINX_THEME default) #alabaster
    endif()

    if(NOT DEFINED SPHINX_THEME_DIR)
        set(SPHINX_THEME_DIR)
    endif()



    # configured documentation tools and intermediate build results
    set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")

    # Sphinx cache with pickled ReST documents
    set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs/_doctrees")

    # HTML output directory
    set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs/html")

    set(CONTAINMENT_FOLDER "${BINARY_BUILD_DIR}/api")

    file(MAKE_DIRECTORY ${BINARY_BUILD_DIR})
    file(MAKE_DIRECTORY ${SPHINX_CACHE_DIR})
    file(MAKE_DIRECTORY ${SPHINX_HTML_DIR})

    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/docs/conf.py.in"
            "${BINARY_BUILD_DIR}/conf.py"
            @ONLY)

    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/docs/index.rst.in"
            "${BINARY_BUILD_DIR}/index.rst"
            @ONLY)

    add_custom_target(zacc.documentation ALL
            ${SPHINX_EXECUTABLE}
            -Q -b html -j auto
            -c "${BINARY_BUILD_DIR}"
            -d "${SPHINX_CACHE_DIR}"
            "${BINARY_BUILD_DIR}"
            "${SPHINX_HTML_DIR}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/docs"
            DEPENDS ${doc.deps}
            COMMENT "Building HTML documentation with Sphinx")

endif()