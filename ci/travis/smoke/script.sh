#!/usr/bin/env bash

cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target zacc.system.info -- -j $JOBS
cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target zacc.examples.mandelbrot -- -j $JOBS
cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} --target zacc.examples.julia -- -j $JOBS

cd "${BUILD_DIR}"

# set shared library path
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${BUILD_DIR}/lib

# display contents
ls ./bin
ls ./lib

# detect system
echo "Execute zacc.system.info"
./bin/zacc.system.info

# run examples
echo "Execute zacc.examples.julia"
./bin/zacc.examples.julia --dim="[1024, 1024]" --headless     

echo "Execute zacc.examples.mandelbrot"
./bin/zacc.examples.mandelbrot --dim="[1024, 1024]" --headless     