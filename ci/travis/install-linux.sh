#!/usr/bin/env bash

#virtualenv venv -p python3
pip install --user -r ${TRAVIS_BUILD_DIR}/ci/requirements.txt
#pip install -r ${TRAVIS_BUILD_DIR}/ci/requirements.txt