#!/usr/bin/env bash

cd ${TRAVIS_BUILD_DIR}

mkdir release

# copy binary files
cp -r ${BUILD_DIR}/bin release/bin
cp -r ${BUILD_DIR}/lib release/lib

# copy dependencies
cp -r ${TRAVIS_BUILD_DIR}/dependencies release/dependencies

# copy sources
cp -r ${TRAVIS_BUILD_DIR}/cmake release/cmake
cp -r ${TRAVIS_BUILD_DIR}/codegen release/codegen

cp -r ${TRAVIS_BUILD_DIR}/examples release/examples
cp -r ${TRAVIS_BUILD_DIR}/include release/include
cp -r ${TRAVIS_BUILD_DIR}/src release/src
cp -r ${TRAVIS_BUILD_DIR}/test release/test
cp -r ${TRAVIS_BUILD_DIR}/CMakeLists.txt release/CMakeLists.txt

cp ${TRAVIS_BUILD_DIR}/LICENSE release/LICENSE
cp ${TRAVIS_BUILD_DIR}/README.md release/README.md

# compress
zip -r release.zip release



