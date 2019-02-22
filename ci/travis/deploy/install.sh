#!/usr/bin/env bash

if [[ $TRAVIS_OS_NAME == 'osx' ]]; then
    source venv/bin/activate
fi

pip install --user -r ./requirements.txt