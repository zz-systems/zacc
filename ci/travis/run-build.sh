#!/usr/bin/env bash

cmake -H../zacc -B${BUILD_DIR} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DBUILD_SANITIZE_MEMORY=${BUILD_SANITIZE_MEMORY}

cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target zacc.system.info -- -j $JOBS
cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target zacc.tests.all -- -j $JOBS
cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target zacc.examples.mandelbrot -- -j $JOBS
cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target zacc.examples.julia -- -j $JOBS