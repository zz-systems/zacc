#!/usr/bin/env bash

brew update
brew upgrade python3
brew install doxygen
brew install sphinx-doc
brew link sphinx-doc --force
brew cask install xquartz

#virtualenv venv -p python3
source venv/bin/activate
pip install --user -r ${TRAVIS_BUILD_DIR}/ci/requirements.txt
#pip install -r ${TRAVIS_BUILD_DIR}/ci/requirements.txt