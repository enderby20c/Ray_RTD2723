#################################
# create build step #0: KCPU firmware code
#################################
set(CPU_TYPE "RX3081")
set(TOOLCHAIN_TYPE "rsdk")
set(BUILD_TEMPLATE "build_KCPU_firmware")

set(CMAKE_OUTPUT_DIR "${OUTPUT_DIR}/CMAKE_KCPU")
set(CMAKE_OUTPUT_DIR_LIST "${CMAKE_OUTPUT_DIR_LIST} \"${CMAKE_OUTPUT_DIR}\"")

configure_file(
    "${SCRIPT_DIR}/template/run_build.sh.in"
    "${CMAKE_OUTPUT_DIR}/run_build.sh"
    @ONLY
)
