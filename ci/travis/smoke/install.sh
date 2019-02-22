#!/usr/bin/env bash

if [[ $TRAVIS_OS_NAME == 'osx' ]]; then
    brew update
    brew upgrade python3
    brew cask install xquartz

    source venv/bin/activate
fi

pip install --user -r ${SCRIPT_STAGE_DIR}/requirements.txt