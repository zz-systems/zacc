#!/usr/bin/env bash

aws s3 sync s3://${AWS_BUCKET}/package ${TRAVIS_BUILD_DIR}/${SHARE_FOLDER}