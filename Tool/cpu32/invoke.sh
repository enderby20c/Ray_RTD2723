#!/usr/bin/env bash

# $1: target project name
PROJECT_NAME=${1}
DIR_NAME=$( basename "${PWD}" )

# run cmake config
cmake -S . -B "../${DIR_NAME}_OUTPUT/${PROJECT_NAME}" -DPROJECT_NAME="${PROJECT_NAME}" -G Ninja

# run build
cmake --build "../${DIR_NAME}_OUTPUT/${PROJECT_NAME}"
