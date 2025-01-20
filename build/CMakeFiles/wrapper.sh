#!/usr/bin/env bash
SCRIPT_PATH=$( realpath "${0}" )
ROOT_PATH=$( dirname "${SCRIPT_PATH}" )

PACKAGE_SRC="D:/data/doc/Raytech/Realtek/Scaler/RTD2723/s1/RTD2723_Series_Source code_Tracking NO_20241015_s1/Tool/cpu32/cpu32_wrapper"
PACKAGE_TARGET="${ROOT_PATH}/cpu32_wrapper"

# check init
if [[ ! -d "${PACKAGE_TARGET}" ]] || \
   [[ "${PACKAGE_SRC}" -nt "${PACKAGE_TARGET}" ]]; then

    rm -rf "${PACKAGE_TARGET}"
    mkdir -p "${PACKAGE_TARGET}"

    tar zxf "${PACKAGE_SRC}" -C "${PACKAGE_TARGET}"
    touch "${PACKAGE_TARGET}"
fi

"${PACKAGE_TARGET}"/cpu32_wrapper "$@"
