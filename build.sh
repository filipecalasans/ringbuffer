#!/usr/bin/env bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

mkdir "$SCRIPT_DIR/out" &> /dev/null || true

CMAKE_DEFINES=()

(cd "$SCRIPT_DIR/out" && cmake ../ "${CMAKE_DEFINES[@]}" && make)

