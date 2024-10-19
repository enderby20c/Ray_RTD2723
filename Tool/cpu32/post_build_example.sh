#!/usr/bin/env bash

# target project name
#   - ex: RLXXXX_Project
PROJECT_NAME=${1}

# path to source code directory
PROJECT_DIR="@PROJECT_DIR@"

# actions
case ${PROJECT_NAME} in
    RL6829_Project)
        echo "post-build command for ${PROJECT_NAME}"
        echo "source code in ${PROJECT_DIR}"
    ;;
esac
