#!/usr/bin/env bash

if [[ $TRAVIS_OS_NAME == 'osx' ]]; then
    brew update
    brew upgrade python3
    brew cask install xquartz
fi

virtualenv -p python3 venv
source venv/bin/activate

pip install -r ${SCRIPT_STAGE_DIR}/requirements.txt