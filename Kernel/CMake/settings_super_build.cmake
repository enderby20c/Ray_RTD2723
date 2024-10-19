# script for super-build

# skip install rules
set(CMAKE_SKIP_INSTALL_RULES True)

# use generic system
set(CMAKE_SYSTEM_NAME "Generic")

# check for in-source build
file(RELATIVE_PATH position "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

if (${position} MATCHES "^[^.].*")
    message(FATAL_ERROR "In-source build is not allowed.")
endif()


#################################
# initialization
#################################
# convert to platform path
get_filename_component(PROJECT_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}"
    ABSOLUTE
)

get_filename_component(PROJECT_CONFIG_PATH
    ${PROJECT_CONFIG_PATH}
    ABSOLUTE
)

# convert output path
get_filename_component(OUTPUT_DIR
    "${CMAKE_CURRENT_BINARY_DIR}"
    ABSOLUTE
)


#################################
# build flow options
#################################
option(REBUILD "run clean before build")
option(DRY_RUN "run cmake configuration and exit")


#################################
# build options
#################################
# Build Type:
#   - Release   : normal usage
#   - Debug     : debug usage
set(BUILD_TYPE "Release" CACHE STRING "Build type")
set_property(CACHE BUILD_TYPE PROPERTY STRINGS "Release;Debug")

option(USE_ASSERT "enable assert functions")

option(USE_PCH "Use PCH(Precompiled Header) to speed up compile process" ON)

option(ASM_SRC_OUTPUT "creates assembler sources (.S) and objects (.obj)" OFF)

option(USE_UNITY_BUILD "Use unity build to speed up compile process" OFF)

option(NO_LINK "Skip linking step" OFF)

# file filter
set(FILE_FILTER "" CACHE STRING "filter to translate single unit")
mark_as_advanced(FILE_FILTER)

# Optimization level
set(OPT_LEVEL "-Odefault" CACHE STRING "optimization level")

# build system options
set(GENERATOR_TYPE "Ninja")

if (${BUILD_TYPE} STREQUAL "Debug")
    set(GENERATOR_TYPE "Eclipse CDT4 - ${GENERATOR_TYPE}")
endif()

# set IDE type to eclipse
set(IDE_TYPE "_ECLIPSE_VERSION=4.6")


#################################
# generate scripts
#################################
file(MAKE_DIRECTORY
    "${OUTPUT_DIR}/COMMON_FILES"
)

# generate build step scripts
set(CMAKE_OUTPUT_DIR_LIST "")
include("${SCRIPT_DIR}/${SCALER_NAME}_script_generator.cmake")

# generate build script
set(TEMPLATE_FILES
    "run_super_build.sh"
)

foreach(template_path ${TEMPLATE_FILES})
    get_filename_component(
        basename
        ${template_path}
        NAME
    )
    configure_file(
        "${SCRIPT_DIR}/template/${template_path}.in"
        "${OUTPUT_DIR}/${basename}"
        @ONLY
    )

    if(${template_path} MATCHES ".*\.sh$")
        execute_process(
            COMMAND
                chmod +x "${OUTPUT_DIR}/${basename}"
        )
    endif()
endforeach()


#################################
# print parameters
#################################
# echo BUILD_SCRIPT location
message("BUILD_SCRIPT=${OUTPUT_DIR}/run_super_build.sh")
message("OUTPUT_DIR=${OUTPUT_DIR}")

# add build target
add_custom_target("build" ALL
        ./run_super_build.sh build_all
    COMMENT
        "invoking build scripts..."
    USES_TERMINAL
)

# add build target
add_custom_target("clean_all"
        ./run_super_build.sh clean_all
    COMMENT
        "invoking clean scripts..."
)
