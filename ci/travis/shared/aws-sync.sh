#!/usr/bin/env bash

aws s3 sync s3://${AWS_BUCKET}/package ${SHARE_DIR}