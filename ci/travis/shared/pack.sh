#!/usr/bin/env bash

# RELEASE_NAME=zacc.${TRAVIS_OS_NAME}
# mkdir ${RELEASE_DIR}
# # copy binary files
# cp -r ${BUILD_DIR}/bin ${RELEASE_DIR}/bin
# cp -r ${BUILD_DIR}/lib ${RELEASE_DIR}/lib

# # copy dependencies
# cp -r ${TRAVIS_BUILD_DIR}/dependencies ${RELEASE_DIR}/dependencies

# # copy sources
# cp -r ${TRAVIS_BUILD_DIR}/cmake ${RELEASE_DIR}/cmake
# cp -r ${TRAVIS_BUILD_DIR}/codegen ${RELEASE_DIR}/codegen

# cp -r ${TRAVIS_BUILD_DIR}/examples ${RELEASE_DIR}/examples
# cp -r ${TRAVIS_BUILD_DIR}/include ${RELEASE_DIR}/include
# cp -r ${TRAVIS_BUILD_DIR}/src ${RELEASE_DIR}/src
# cp -r ${TRAVIS_BUILD_DIR}/test ${RELEASE_DIR}/test
# cp -r ${TRAVIS_BUILD_DIR}/CMakeLists.txt ${RELEASE_DIR}/CMakeLists.txt

# cp ${TRAVIS_BUILD_DIR}/LICENSE ${RELEASE_DIR}/LICENSE
# cp ${TRAVIS_BUILD_DIR}/README.md ${RELEASE_DIR}/README.md

# # compress
# zip -r ${RELEASE_NAME}.zip ${RELEASE_DIR}

# cp ./${RELEASE_NAME}.zip ${SHARE_DIR}