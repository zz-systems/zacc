#!/usr/bin/env bash

cmake --build . --config %BUILD_TYPE% --target zacc.system.detect -- -j 4
cmake --build . --config %BUILD_TYPE% --target zacc.tests.all -- -j 4