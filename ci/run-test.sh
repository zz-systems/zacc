#!/usr/bin/env bash

cd "${TRAVIS_BUILD_DIR}/${BUILD_DIR}"

# set shared library path
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${TRAVIS_BUILD_DIR}/lib

# display contents
ls ./bin
ls ./lib

# detect system
./bin/zacc.system.detect

# run tests
ctest --output-on-failure

# run examples
# TODO