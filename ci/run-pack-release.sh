#!/usr/bin/env bash

cd ${TRAVIS_BUILD_DIR}

mkdir ${RELEASE_NAME}

# copy binary files
cp -r ${BUILD_DIR}/bin ${RELEASE_NAME}/bin
cp -r ${BUILD_DIR}/lib ${RELEASE_NAME}/lib

# copy dependencies
cp -r ${TRAVIS_BUILD_DIR}/dependencies ${RELEASE_NAME}/dependencies

# copy sources
cp -r ${TRAVIS_BUILD_DIR}/cmake ${RELEASE_NAME}/cmake
cp -r ${TRAVIS_BUILD_DIR}/codegen ${RELEASE_NAME}/codegen

cp -r ${TRAVIS_BUILD_DIR}/examples ${RELEASE_NAME}/examples
cp -r ${TRAVIS_BUILD_DIR}/include ${RELEASE_NAME}/include
cp -r ${TRAVIS_BUILD_DIR}/src ${RELEASE_NAME}/src
cp -r ${TRAVIS_BUILD_DIR}/test ${RELEASE_NAME}/test
cp -r ${TRAVIS_BUILD_DIR}/CMakeLists.txt ${RELEASE_NAME}/CMakeLists.txt

cp ${TRAVIS_BUILD_DIR}/LICENSE ${RELEASE_NAME}/LICENSE
cp ${TRAVIS_BUILD_DIR}/README.md ${RELEASE_NAME}/README.md

# compress
#zip -r release.zip ${RELEASE_NAME}



