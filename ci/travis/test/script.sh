#!/usr/bin/env bash

cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target zacc_cpuid -- -j $JOBS
cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target mandelbrot -- -j $JOBS
cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target julia -- -j $JOBS
cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target zacc.tests.all -- -j $JOBS

cd "${BUILD_DIR}"

# set shared library path
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${BUILD_DIR}/lib

# display contents
ls ./bin
ls ./lib

# detect system
echo "Execute zacc.system.info"
./bin/zacc_cpuid

# run tests
echo "Execute tests"
ctest --output-on-failure

# run examples
echo "Execute julia"
./bin/julia --dim="[1024, 1024]" --headless

echo "Execute mandelbrot"
./bin/mandelbrot --dim="[1024, 1024]" --headless