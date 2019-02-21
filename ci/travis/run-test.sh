#!/usr/bin/env bash

cd "${BUILD_DIR}"

# set shared library path
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${BUILD_DIR}/lib

# display contents
ls ./bin
ls ./lib

# detect system
echo "Execute zacc.system.info"
./bin/zacc.system.info

# run tests
echo "Execute tests"
ctest --output-on-failure

# run examples
echo "Execute zacc.examples.julia"
xvfb-run zacc.examples.julia

echo "Execute zacc.examples.mandelbrot"
xvfb-run zacc.examples.mandelbrot