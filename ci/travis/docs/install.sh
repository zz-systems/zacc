#!/usr/bin/env bash

if [[ $TRAVIS_OS_NAME == 'osx' ]]; then
    brew update
    brew upgrade python3
    brew install doxygen
    brew install sphinx-doc
    brew link sphinx-doc --force

    source venv/bin/activate
fi

pip install --user -r "${0%/*}"/requirements.txt