#!/usr/bin/env bash

cd "${TRAVIS_BUILD_DIR}/${BUILD_DIR}"

cmake --build . --config %BUILD_TYPE% --target zacc.documentation