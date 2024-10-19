# script for building project

# use relative path because gcc embedded compiler only support relative path
set(CMAKE_USE_RELATIVE_PATHS ON)

if(NOT ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    # Maximum object file full-path length allowed by native build tools.
    set(CMAKE_OBJECT_PATH_MAX 240)
endif()


#################################
# compiler options
#################################
# set elf suffix
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# other gcc tools
get_filename_component(GCC_ROOT ${CMAKE_C_COMPILER} DIRECTORY)
get_filename_component(GCC_PREFIX ${CMAKE_C_COMPILER} NAME_WE)
string(REPLACE "gcc" "" GCC_PREFIX ${GCC_PREFIX})

set(CMAKE_AR            ${GCC_ROOT}/${GCC_PREFIX}ar)
set(CMAKE_RANLIB        ${GCC_ROOT}/${GCC_PREFIX}ranlib)
set(CMAKE_NM            ${GCC_ROOT}/${GCC_PREFIX}nm)
set(CMAKE_STRIP         ${GCC_ROOT}/${GCC_PREFIX}strip)
set(CMAKE_LINKER        ${GCC_ROOT}/${GCC_PREFIX}ld)

set(SIZE                ${GCC_ROOT}/${GCC_PREFIX}size)
set(OBJDUMP             ${GCC_ROOT}/${GCC_PREFIX}objdump)
set(OBJCOPY             ${GCC_ROOT}/${GCC_PREFIX}objcopy)
set(NM                  ${GCC_ROOT}/${GCC_PREFIX}nm)
set(CPP                 ${GCC_ROOT}/${GCC_PREFIX}cpp)

set(OBJDUMP_FLAGS       "-rth")

# compile options
set(GLOBAL_ASMFLAGS
    ${ARCH_FLAGS}
    "-x assembler-with-cpp"
    "-fstack-usage"
)
set(GLOBAL_CFLAGS
    ${ARCH_FLAGS}
    "-std=gnu11"
    "-fshort-enums"
    "-fno-section-anchors"
    "-fno-merge-constants"
    "-fstack-usage"
)
set(GLOBAL_CXXFLAGS
    ${ARCH_FLAGS}
    "-std=gnu++11"
    "-fshort-enums"
    "-fno-section-anchors"
    "-fno-merge-constants"
    "-fstack-usage"
)
set(GLOBAL_LDFLAGS
    ${ARCH_FLAGS}
    "-nostartfiles"
    "-Xlinker --gc-sections"
)

list(JOIN ARCH_FLAGS " " ARCH_FLAGS_STR)

# archive options
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcD <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_APPEND "<CMAKE_AR> qD  <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcD <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_APPEND "<CMAKE_AR> qD  <TARGET> <LINK_FLAGS> <OBJECTS>")


#################################
# project default settings
#################################
if(NOT DEFINED LINKER_FILE_CPU32)
    set(LINKER_FILE_CPU32
        "Project/Header/${PROJECT_NAME}_Link.ld"
    )
endif()


#################################
# project directory options
#################################
# convert to absolute path
get_filename_component(KERNEL_DIR
    ${KERNEL_DIR}
    ABSOLUTE
)

# convert output path
get_filename_component(OUTPUT_DIR
    "${CMAKE_CURRENT_BINARY_DIR}/.."
    ABSOLUTE
)

# convert user path
set(ABS_USER_DIRS "")

foreach(user_dir ${USER_DIRS})
    get_filename_component(USER_DIR
        ${user_dir}
        ABSOLUTE
    )

    set(ABS_USER_DIRS ${ABS_USER_DIRS} ${USER_DIR})
endforeach()

set(ABS_USER_DEVICE_DIRS "")

foreach(user_device_dir ${USER_DEVICE_DIRS})
    get_filename_component(USER_DEVICE_DIR
        ${user_device_dir}
        ABSOLUTE
    )

    set(ABS_USER_DEVICE_DIRS ${ABS_USER_DEVICE_DIRS} ${USER_DEVICE_DIR})
endforeach()

set(ABS_USER_EMBEDDED_RESOURCE_DIRS "")

if(DEFINED USER_EMBEDDED_RESOURCE_DIRS)
    foreach(user_resource_dir ${USER_EMBEDDED_RESOURCE_DIRS})
        get_filename_component(USER_RESOURCE_DIR
            ${user_resource_dir}
            ABSOLUTE
        )

        set(ABS_USER_EMBEDDED_RESOURCE_DIRS ${ABS_USER_EMBEDDED_RESOURCE_DIRS} ${USER_RESOURCE_DIR})
    endforeach()
endif()


#################################
# build environment settings
#################################
execute_process(
    COMMAND
        ninja --version
    OUTPUT_VARIABLE
        NINJA_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND
        uname -sro
    OUTPUT_VARIABLE
        SYSTEM_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)


#################################
# build template
#################################
# load build template
include("${BUILD_TEMPLATE_PATH}")

# print configuration
message(STATUS "***********************************************************************")
message(STATUS "SYSTEM_VERSION      = ${SYSTEM_VERSION}")
message(STATUS "CMAKE_VERSION       = ${CMAKE_VERSION}")
message(STATUS "NINJA_VERSION       = ${NINJA_VERSION}")
message(STATUS "PROJECT_NAME        = ${PROJECT_NAME}")
message(STATUS "SCALER_NAME         = ${SCALER_NAME}")
message(STATUS "CPU_TYPE            = ${CPU_TYPE}")
message(STATUS "KERNEL_DIR          = ${KERNEL_DIR}")
message(STATUS "USER_DIRS           = ${USER_DIRS}")
message(STATUS "OUTPUT_DIR          = ${OUTPUT_DIR}")
message(STATUS "C_DEFINE            = ${C_DEFINE}")
message(STATUS "C_INCLUDE           = ${C_INCLUDE}")
message(STATUS "CMAKE_BUILD_TYPE    = ${CMAKE_BUILD_TYPE}")
message(STATUS "USE_ASSERT          = ${USE_ASSERT}")
message(STATUS "USE_PCH             = ${USE_PCH}")
message(STATUS "USE_UNITY_BUILD     = ${USE_UNITY_BUILD}")
message(STATUS "NO_LINK             = ${NO_LINK}")
message(STATUS "***********************************************************************")
