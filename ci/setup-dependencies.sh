#!/usr/bin/env bash

# setup dependencies folder
DEPS_DIR="${TRAVIS_BUILD_DIR}/deps"
mkdir -p ${DEPS_DIR} && cd ${DEPS_DIR}

# install cmake
if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
    CMAKE_URL="http://www.cmake.org/files/v3.6/cmake-3.6.0-Linux-x86_64.tar.gz"
    mkdir cmake && travis_retry wget --quiet -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake
    export PATH=${DEPS_DIR}/cmake/bin:${PATH}
fi

pip install --user -r ${TRAVIS_BUILD_DIR}/ci/requirements.txt