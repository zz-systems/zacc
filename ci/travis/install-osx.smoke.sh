#!/usr/bin/env bash

brew update
brew upgrade python3
brew cask install xquartz

#virtualenv venv -p python3
source venv/bin/activate
pip install --user -r ${TRAVIS_BUILD_DIR}/ci/requirements.smoke.txt
#pip install -r ${TRAVIS_BUILD_DIR}/ci/requirements.txt

mkdir -p ~/$TRAVIS_BUILD_NUMBER
aws s3 sync s3://${bucket}/$TRAVIS_BUILD_NUMBER ~/$TRAVIS_BUILD_NUMBER