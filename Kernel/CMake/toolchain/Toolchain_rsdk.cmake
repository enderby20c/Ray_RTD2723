set(CMAKE_SYSTEM_NAME Generic)

# set toolchain version
set(TOOLCHAIN_VERSION "rsdk-10.2.0")

# specify the cross compiler
INCLUDE(CMakeForceCompiler)

# construct search path
set(TOOLCHAIN_SEARCH_PATH
    "/opt/RTK-MNT-ToolChain/${TOOLCHAIN_VERSION}"
)

# add windows path
set(DRIVE_NAME_LIST
    "c" "d" "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "o" "p" "q" "r" "s" "t" "u" "v" "w" "x" "y" "z"
)

foreach (drive_name ${DRIVE_NAME_LIST})
    set(TOOLCHAIN_SEARCH_PATH
        ${TOOLCHAIN_SEARCH_PATH}
        "/${drive_name}/RTK-MNT-ToolChain/${TOOLCHAIN_VERSION}"
        "/mnt/${drive_name}/RTK-MNT-ToolChain/${TOOLCHAIN_VERSION}"
    )
endforeach()

set(TOOLCHAIN_SEARCH_PATH_SUFFIXES
    "mingw32/newlib/bin"
    "linux/newlib/bin"
    "cygwin/newlib/bin"
)

find_program (
    C_PROGRAM
    NAMES
        "mips-elf-gcc"
        "rsdk-elf-gcc"
    PATHS
        ${TOOLCHAIN_SEARCH_PATH}
    PATH_SUFFIXES
        ${TOOLCHAIN_SEARCH_PATH_SUFFIXES}
    NO_DEFAULT_PATH
)

find_program (
    CPP_PROGRAM
    NAMES
        "mips-elf-g++"
        "rsdk-elf-g++"
    PATHS
        ${TOOLCHAIN_SEARCH_PATH}
    PATH_SUFFIXES
        ${TOOLCHAIN_SEARCH_PATH_SUFFIXES}
    NO_DEFAULT_PATH
)

# set C/C++ compiler
set(CMAKE_C_COMPILER "${C_PROGRAM}")
set(CMAKE_CXX_COMPILER "${CPP_PROGRAM}")

# override default GNU flags
set(CMAKE_C_FLAGS_RELEASE   "" CACHE STRING "C flags for release")
set(CMAKE_CXX_FLAGS_RELEASE "" CACHE STRING "CXX flags for release")
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE STRING "ASM flags for release")

# where is the target environment
get_filename_component(GCC_ROOT ${CMAKE_C_COMPILER} DIRECTORY)
set(CMAKE_FIND_ROOT_PATH  ${GCC_ROOT})

# search for programs in the build host directories
#   - for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# compile options
set(ARCH_FLAGS
    "-march=3081"

    # fix RX3081 unaligned branch issue
    "-mfix-rx3081"

    # little-endian
    "-EL"

    # instructions must not access executable sections (ex: register address)
    #   - prevent cache miss
    "-mcode-readable=no"

    # allocate variables to the read-only data section first if possible
    #   - no .sdata sections
    "-membedded-data"

    # do not generate .rodata.CSWTCH sections for switch-case
    "-fno-tree-switch-conversion"

    # limit the amount of jump tables created by switch-case
    #   - only if jump table reduces total code size
    "--param=jump-table-max-growth-ratio-for-size=100"
)

if(${USE_ASSERT})
    set(
        ARCH_FLAGS
        ${ARCH_FLAGS}
        # enable div-by-zero check
        "-mcheck-zero-division"
    )
else()
    set(
        ARCH_FLAGS
        ${ARCH_FLAGS}
        # disable div-by-zero check
        "-mno-check-zero-division"
    )
endif()
