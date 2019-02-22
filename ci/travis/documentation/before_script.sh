#!/usr/bin/env bash

eval "${MATRIX_EVAL}"
export CC=${CC}
export CXX=${CXX}

cmake -H../zacc -B${BUILD_DIR} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DBUILD_TESTS=0 -DBUILD_EXAMPLES=0 -DBUILD_DOCS=1