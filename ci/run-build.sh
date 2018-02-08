#!/usr/bin/env bash

cd "${TRAVIS_BUILD_DIR}/${BUILD_DIR}"

cmake --build . --config ${BUILD_TYPE} --target zacc.system.detect -- -j 4
cmake --build . --config ${BUILD_TYPE} --target zacc.tests.all -- -j 4
cmake --build . --config ${BUILD_TYPE} --target zacc.examples -- -j 4