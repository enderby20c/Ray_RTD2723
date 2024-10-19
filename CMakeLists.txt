cmake_minimum_required(VERSION 3.16)

set(CMAKE_NINJA_FORCE_RESPONSE_FILE ON)

#################################
# project settings
#################################
if(DEFINED PROJECT_NAME)
    # search for config by project name
    set(TARGET_PROJECT_NAME "${PROJECT_NAME}")
else()
    # use the first project if not defined
    set(TARGET_PROJECT_NAME "first")
endif()

# load project list
include("CMakeProjectList.cmake")

# collect project names
set(PROJECT_LIST "")

foreach(project_config ${PROJECT_CONFIG_LIST})

    # reset variables
    set(PROJECT_NAME "none")

    include("${project_config}")

    if("${PROJECT_NAME}" STREQUAL "none")
        message(WARNING "invalid config file: ${project_config}")
        continue()
    endif()

    set(PROJECT_LIST ${PROJECT_LIST} ${PROJECT_NAME})
endforeach()

if (DEFINED CMAKE_SCRIPT_MODE_FILE)

    # special action: list all project names and return
    foreach(project_name ${PROJECT_LIST})
        message("PROJECT_NAME=${project_name}")
    endforeach()

    return()

else()

    foreach(project_config ${PROJECT_CONFIG_LIST})

        # unset optional variables
        unset(KERNEL_DIR)
        unset(LINKER_FILE_CPU32)
        unset(USER_POST_BUILD_SCRIPT)
        unset(USER_EMBEDDED_RESOURCE_DIRS)

        include("${project_config}")

        if("${TARGET_PROJECT_NAME}" STREQUAL "first" OR
                "${TARGET_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")

            set(TARGET_PROJECT_NAME "${PROJECT_NAME}")
            set(PROJECT_CONFIG_PATH "${project_config}")
            break()

        endif()

    endforeach()

    if(NOT "${TARGET_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
        message(FATAL_ERROR "project not found: ${TARGET_PROJECT_NAME}")
    endif()

    set(PROJECT_NAME "${TARGET_PROJECT_NAME}" CACHE STRING "Project name")
    set_property(CACHE PROJECT_NAME PROPERTY STRINGS ${PROJECT_LIST})

endif()


#################################
# project default settings
#################################
if(NOT DEFINED KERNEL_DIR)
    set(KERNEL_DIR
        "./Kernel"
    )
endif()


#################################
# tool settings
#################################
# path to cmake scripts
get_filename_component(SCRIPT_DIR
    "${KERNEL_DIR}/CMake"
    ABSOLUTE
)

# path to cpu32 wrapper
if (NOT DEFINED WRAPPER_BIN)
    set(WRAPPER_BIN "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/wrapper.sh")
endif()

if (NOT EXISTS ${WRAPPER_BIN})

    if(NOT ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
        set(WRAPPER_PACKAGE "cpu32_wrapper")
    else()
        set(WRAPPER_PACKAGE "cpu32_wrapper_unix")
    endif()

    configure_file(
        "${SCRIPT_DIR}/template/wrapper.sh.in"
        "${WRAPPER_BIN}"
        @ONLY
    )

    if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
        execute_process(
            COMMAND
                chmod +x "${WRAPPER_BIN}"
        )
    endif()

endif()


#################################
# build settings
#################################
if(NOT DEFINED SKIP_META_BUILD)

    project(${PROJECT_NAME} NONE)

    # run super build
    include("${SCRIPT_DIR}/settings_super_build.cmake")

else()

    # C/CPP/asm files
    project(${PROJECT_NAME} C CXX ASM)

    # run build
    include("${SCRIPT_DIR}/settings_build.cmake")

endif()
