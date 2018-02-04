#!/usr/bin/env bash

# setup dependencies folder
DEPS_DIR="${TRAVIS_BUILD_DIR}/deps"
mkdir -p ${DEPS_DIR} && cd ${DEPS_DIR}

PIP_BASE_PACKAGES="pyopenssl ndg-httpsclient pyasn1"
PIP_PACKAGES="yasha sphinx breathe exhale"

# install cmake
if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
    CMAKE_URL="http://www.cmake.org/files/v3.6/cmake-3.6.0-Linux-x86_64.tar.gz"
    mkdir cmake && travis_retry wget --quiet -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake
    export PATH=${DEPS_DIR}/cmake/bin:${PATH}
else
    pip install --user -r ./requirements.txt
fi