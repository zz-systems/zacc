#!/usr/bin/env bash

cd ${TRAVIS_BUILD_DIR}

mkdir release

# copy binary files
cp ${BUILD_DIR}/bin ${TRAVIS_BUILD_DIR}/release/bin
cp ${BUILD_DIR}/lib ${TRAVIS_BUILD_DIR}/release/lib

# copy dependencies
cp -r ${BUILD_DIR}/dependencies ${TRAVIS_BUILD_DIR}/release/dependencies

# copy sources
cp -r ${BUILD_DIR}/cmake ${TRAVIS_BUILD_DIR}/release/cmake
cp -r ${BUILD_DIR}/codegen ${TRAVIS_BUILD_DIR}/release/codegen

cp -r ${BUILD_DIR}/examples release/examples
cp -r ${BUILD_DIR}/include release/include
cp -r ${BUILD_DIR}/src release/src
cp -r ${BUILD_DIR}/test release/test
cp -r ${BUILD_DIR}/CMakeLists.txt release/CMakeLists.txt

cp ${BUILD_DIR}/LICENSE release/LICENSE
cp ${BUILD_DIR}/README.md release/README.md

# compress
zip -r release.zip release



