#!/usr/bin/env bash

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    brew update
    brew install python3
    virtualenv venv -p python3
    source venv/bin/activate
fi