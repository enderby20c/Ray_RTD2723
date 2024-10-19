#################################
# project settings
#   - manatory
#################################
# project name
set(PROJECT_NAME
    "RLXXXX_Project"
)

# scaler name
set(SCALER_NAME
    "RLXXXX"
)

# paths to User directories
#   - relative to project root
set(USER_DIRS
    "./User/XXXX_Factory"
    "./User/XXXX_Series"
)

# paths to User device directories
#   - relative to project root
#   - LED driver, PMIC, etc.
set(USER_DEVICE_DIRS
    "./User/Device"
)

# C define
#   - syntax: "A=B"
#   - no spaces required. Ex: "A = B" is invalid
set(C_DEFINE
    "_PROJECT=_XXXX_PROJECT"
    "_SCALER_TYPE=_RLXXXX_SERIES"
)

# C include
#   - relative to project root
set(C_INCLUDE
    "./Project/Header"
    "./Pcb"
    "./Panel"

    "./User/Device/Header"
    "./User/XXXX_Series/XXXXUserInterface/Header"
    "./User/XXXX_Series/XXXXFunction/Header"
    "./User/XXXX_Series/XXXXOsd/Header"
    "./User/XXXX_Factory/Header"
)


#################################
# optional settings
#   - use default value if not provided
#################################
# path to Kernel directory
#   - relative to project root
#   - default: Kernel/ in project root
set(KERNEL_DIR
    "./Kernel"
)

# path to cpu32 linker file (.ld)
#   - relative to project root
#   - default: use PROJECT_NAME + "_Link.ld"
set(LINKER_FILE_CPU32
    "Project/Header/${PROJECT_NAME}_Link.ld"
)

# script run after build
#   - with PROJECT_NAME as the first argument
#   - default: undefined
set(USER_POST_BUILD_SCRIPT
    "Tool/cpu32/post_build_example.sh"
)

# resource files to be embedded in firmware
#   - resource directory
set(USER_EMBEDDED_RESOURCE_DIRS
    "./User/RTD_Series/RTD2020Resource"
)
