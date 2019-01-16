#!/usr/bin/env bash

brew update
brew upgrade python3
brew install doxygen
brew install sphinx-doc
brew link sphinx-doc --force
brew cask install xquartz
virtualenv venv -p python3
source venv/bin/activate