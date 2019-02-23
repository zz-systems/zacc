#!/usr/bin/env bash

virtualenv -p python3 venv
source venv/bin/activate

pip install -r ${SCRIPT_STAGE_DIR}/requirements.txt