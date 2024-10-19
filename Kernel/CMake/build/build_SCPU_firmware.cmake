#################################
# build script for 32-bit second CPU(SCPU)
#################################
set(BUILD_TEMPLATE "build_SCPU_firmware")

if( NO_LINK )
    add_library(${PROJECT_NAME}_SCPU OBJECT)
else()
    add_executable(${PROJECT_NAME}_SCPU)
endif()

add_custom_target(${PROJECT_NAME} ALL
    DEPENDS
        ${PROJECT_NAME}_SCPU
)


#################################
# include path settings for .h files
#################################
target_include_directories(${PROJECT_NAME}_SCPU PUBLIC
    # add kernel include path
    "${KERNEL_DIR}/Common/Arch/Cmsis/system/include"
    "${KERNEL_DIR}/Common/Arch/Cmsis/system/include/cmsis/${CPU_TYPE}"
    "${KERNEL_DIR}/Common/Arch/CPU/${CPU_TYPE}/include/cmsis"
    "${KERNEL_DIR}/Common/3rdParty"

    "${PROJECT_DIR}"
    "${KERNEL_DIR}/Device/Header"
    "${KERNEL_DIR}/Common"
    "${KERNEL_DIR}/Link"
    "${KERNEL_DIR}/System/Header"
    "${KERNEL_DIR}/Scaler/ScalerFunction/Header"
    "${KERNEL_DIR}/Scaler/${SCALER_NAME}_Series_Scaler/Header"
    "${KERNEL_DIR}/UserCommonFunction/Header"

    # add user-defined include path
    ${C_INCLUDE}

    # output directory for binary image
    "${OUTPUT_DIR}/COMMON_FILES/"
)


#################################
# C #define settings
#################################
target_compile_definitions(${PROJECT_NAME}_SCPU PUBLIC
    "_CPU32_IP=_CPU32_IP_${CPU_TYPE}"
    "_HW_CPU32_IS_BOOT_CPU=_FALSE"

    # add user-defined C #define
    ${C_DEFINE}

    # add generated C #define
    "REENTRANT_SYSCALLS_PROVIDED"
    "USE_HAL_DRIVER"
)

if(USE_ASSERT)
    target_compile_definitions(${PROJECT_NAME}_SCPU PUBLIC
        "USE_FULL_ASSERT"
    )
endif()

# add resource flags
if(ABS_USER_EMBEDDED_RESOURCE_DIRS)
    target_compile_definitions(${PROJECT_NAME}_SCPU PUBLIC
        "_EMBEDDED_RESOURCE_FILE_SUPPORT=_ON"
    )
endif()


#################################
# compiler flag settings
#################################
if (NOT ASM_SRC_OUTPUT)
    set(CMAKE_C_COMPILE_OBJECT
        "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>"
    )
else()
    set(CMAKE_C_COMPILE_OBJECT
        "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -S -o <OBJECT>.S -c <SOURCE> && <CMAKE_ASM_COMPILER> ${ARCH_FLAGS_STR} -o <OBJECT> -c <OBJECT>.S"
    )
endif()

set(CMAKE_ASM_COMPILE_OBJECT
    "<CMAKE_ASM_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>"
)

set(POST_COMPILE_CMD
    "./build_actions_post_complier.sh <OBJECT>"
)

# use source in msys2
if(NOT ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(POST_COMPILE_CMD
        "source ${POST_COMPILE_CMD}"
    )
endif()

set(CMAKE_C_COMPILE_OBJECT
    "${CMAKE_C_COMPILE_OBJECT} && ${POST_COMPILE_CMD}"
)

set(CMAKE_ASM_COMPILE_OBJECT
    "${CMAKE_ASM_COMPILE_OBJECT} && ${POST_COMPILE_CMD}"
)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dump")

# common compile flags
target_compile_options(${PROJECT_NAME}_SCPU PUBLIC
    "-Wall"
    "-Wundef"
    "-Wextra"
    "-fmessage-length=0"
    "-fsigned-char"
    "-ffunction-sections"
    "-fdata-sections"
    "-ffreestanding"
    "-fno-move-loop-invariants"
    "-fno-common"
    "-fno-delete-null-pointer-checks"
    "-MMD"
    "-MP"
    "-g1"
    "-O3"
)

# language-specific compile flags
string(JOIN " " C_FLAGS
    ${GLOBAL_CFLAGS}
    "-Wno-discarded-qualifiers"
    "-Wno-discarded-array-qualifiers"
)

string(JOIN " " CXX_FLAGS
    ${GLOBAL_CXXFLAGS}
    "-fabi-version=0"
    "-fno-exceptions"
    "-fno-rtti"
    "-fno-use-cxa-atexit"
    "-fno-threadsafe-statics"
)

string(JOIN " " ASM_FLAGS
    ${GLOBAL_ASMFLAGS}
)


#################################
# try compile settings
#################################
include("${SCRIPT_DIR}/test_condition.cmake")

test_condition_check(${PROJECT_NAME}_SCPU)

test_condition(
    ${PROJECT_NAME}_SCPU
    "_SCPU_BUILD_KCPU_FILES == _ON"
    BUILD_KCPU_FILES
)

test_condition(
    ${PROJECT_NAME}_SCPU
    "_CPU32_SCPU_PROGRAM_TEXT_ON_FLASH == _ON"
    TEXT_ON_FLASH
)

if( NOT USE_UNITY_BUILD )
    test_condition(
        ${PROJECT_NAME}_SCPU
        "_UNITY_BUILD_SUPPORT == _ON"
        USE_UNITY_BUILD
    )
endif()


#################################
# custom settings
#################################
# use -Os if text is on flash
if (TEXT_ON_FLASH)
    target_compile_options(${PROJECT_NAME}_SCPU PUBLIC
        "-Os"
    )
endif()

# add custom optimization level
if(NOT ${OPT_LEVEL} STREQUAL "-Odefault")
    target_compile_options(${PROJECT_NAME}_SCPU PUBLIC
        "${OPT_LEVEL}"
    )
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME}_SCPU PUBLIC
        "DEBUG"
        "OS_USE_TRACE_SEMIHOSTING_DEBUG"
    )

    target_compile_options(${PROJECT_NAME}_SCPU PUBLIC
        "-g3"
        "-Og"
    )
endif()


#################################
# linker settings
#################################
if( NOT NO_LINK )
    # link related files
    set(PROJECT_LINK_FILE
        "${OUTPUT_DIR}/COMMON_FILES/${PROJECT_NAME}_SCPU.ld"
    )
    set(PROJECT_MAP_FILE
        "${OUTPUT_DIR}/COMMON_FILES/${PROJECT_NAME}_SCPU.map"
    )
    set(PROJECT_LOCATION_FILE
        "${OUTPUT_DIR}/COMMON_FILES/${PROJECT_NAME}_SCPU.ld.syms"
    )

    string(JOIN " " LD_FLAGS
        ${GLOBAL_LDFLAGS}
        "--specs=nosys.specs"
        "-Wl,--sort-section=name"
        "-Wl,-T\"${PROJECT_LINK_FILE}\""
        "-Wl,-Map,\"${PROJECT_MAP_FILE}\""
        "-Wl,-R,\"${PROJECT_LOCATION_FILE}\""
    )

    if (BUILD_KCPU_FILES)
        string(APPEND LD_FLAGS
            " -Wl,@actor_wrap_cmd.ld"
        )
    endif()

    set_target_properties(${PROJECT_NAME}_SCPU PROPERTIES
        RULE_LAUNCH_LINK
            "./auto_link32_wrapper.sh"
        LINK_FLAGS
            ${LD_FLAGS}
        RUNTIME_OUTPUT_DIRECTORY
            "${OUTPUT_DIR}/COMMON_FILES"
    )

    # generate .ld template
    configure_file(
        "${KERNEL_DIR}/Link/${SCALER_NAME}_Link.ld"
        "${CMAKE_OUTPUT_DIR}/ld_template.ld"
        @ONLY
    )
endif()


#################################
# custom command settings
#################################
add_custom_target("pre_build"
        ./build_actions_SCPU_firmware.sh pre_build
    DEPENDS
        "${CMAKE_OUTPUT_DIR}/cpp_cmd.sh"
        "${CMAKE_OUTPUT_DIR}/gcc_cmd.sh"
    COMMENT
        "run pre-build"
)

if( NOT NO_LINK )
    add_custom_command(TARGET ${PROJECT_NAME}_SCPU
        PRE_LINK
            COMMAND
                ./build_actions_SCPU_firmware.sh pre_link
            COMMENT
                "run pre-link"
    )

    add_custom_command(TARGET ${PROJECT_NAME}_SCPU
        POST_BUILD
            COMMAND
                ./build_actions_SCPU_firmware.sh post_build
            COMMENT
                "run post-build"
    )
endif()

add_custom_target("clean_all"
        ./build_actions_SCPU_firmware.sh clean_all
    COMMENT
        "run clean"
)


#################################
# custom compiler command settings
#################################
# custom build script
add_custom_command(
    OUTPUT
        "${CMAKE_OUTPUT_DIR}/gcc_cmd.sh"
    COMMAND
        echo ${CMAKE_C_COMPILER} ${C_FLAGS} "$<JOIN:$<TARGET_PROPERTY:${PROJECT_NAME}_SCPU,COMPILE_OPTIONS>, >" "-D$<JOIN:$<TARGET_PROPERTY:${PROJECT_NAME}_SCPU,COMPILE_DEFINITIONS>, -D>" "-I\"$<JOIN:$<TARGET_PROPERTY:${PROJECT_NAME}_SCPU,INCLUDE_DIRECTORIES>,\" -I\">\"" "\"\$\$\"*" > "${CMAKE_OUTPUT_DIR}/gcc_cmd.sh"
    COMMAND
        chmod +x "${CMAKE_OUTPUT_DIR}/gcc_cmd.sh"
)

# CPP script
add_custom_command(
    OUTPUT
        "${CMAKE_OUTPUT_DIR}/cpp_cmd.sh"
    COMMAND
        echo ${CPP} "-D$<JOIN:$<TARGET_PROPERTY:${PROJECT_NAME}_SCPU,COMPILE_DEFINITIONS>, -D>" "-I\"$<JOIN:$<TARGET_PROPERTY:${PROJECT_NAME}_SCPU,INCLUDE_DIRECTORIES>,\" -I\">\"" "\"\$\$\"*" > "${CMAKE_OUTPUT_DIR}/cpp_cmd.sh"
    COMMAND
        chmod +x "${CMAKE_OUTPUT_DIR}/cpp_cmd.sh"
)


#################################
# pre-compiled header (PCH) settings
#################################
if( USE_PCH )

    target_include_directories(${PROJECT_NAME}_SCPU BEFORE PUBLIC
        # add PCH header path
        "${CMAKE_CURRENT_BINARY_DIR}/pch"
    )

    # add dependency from PCH files
    target_compile_options(${PROJECT_NAME}_SCPU PUBLIC
        "-fpch-deps"
    )

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/pch")

    set(PCH_LIST
        "${KERNEL_DIR}/Scaler/ScalerFunction/Header/ScalerFunctionInclude.h"
        "${KERNEL_DIR}/System/Header/SysInclude.h"
        "${KERNEL_DIR}/UserCommonFunction/Header/UserCommonInclude.h"
    )

    foreach(pch_h_path ${PCH_LIST})

        # get file name
        get_filename_component(pch_h_name ${pch_h_path} NAME)

        add_custom_command(
            OUTPUT
                ${pch_h_name}.gch
            COMMAND
                ./pch_wrapper.sh "${pch_h_path}" pch/${pch_h_name}.gch
            BYPRODUCTS
                pch/${pch_h_name}.gch
                pch/${pch_h_name}.d
                pch/${pch_h_name}.su
                pch/${pch_h_name}.gch.txt
        )
    endforeach()

    add_custom_target(pch_target ALL
        DEPENDS
            "ScalerFunctionInclude.h.gch"
            "SysInclude.h.gch"
            "UserCommonInclude.h.gch"
    )

    add_dependencies(${PROJECT_NAME}_SCPU
        pch_target
    )
endif()


#################################
# generate templates
#################################
set(TEMPLATE_FILES
    "build_actions/build_actions_SCPU_firmware.sh"
    "build_actions/build_actions_post_complier.sh"
    "build_actions/build_actions_clipping.sh"
    "build_actions/build_actions_data_section_rename.sh"
    "build_actions/${SCALER_NAME}_build_actions.sh"
    "wrapper/pch_wrapper.sh"
    "wrapper/auto_link32_wrapper.sh"
    "helper.sh"

    # options
    "build_options_clipping"
    "build_options_rename_ddr_data"
    "build_options_rename_xram_data"
)

foreach(template_path ${TEMPLATE_FILES})
    get_filename_component(
        basename
        ${template_path}
        NAME
    )

    if (EXISTS "${SCRIPT_DIR}/template/${template_path}.in")
        configure_file(
            "${SCRIPT_DIR}/template/${template_path}.in"
            "${CMAKE_OUTPUT_DIR}/${basename}"
            @ONLY
        )
    else()
        file(TOUCH
            "${CMAKE_OUTPUT_DIR}/${basename}"
        )
    endif()

    if(${template_path} MATCHES ".*\.sh$")
        execute_process(
            COMMAND
                chmod +x "${CMAKE_OUTPUT_DIR}/${basename}"
        )
    endif()
endforeach()


#################################
# unity build settings
#################################
if( USE_UNITY_BUILD )

    # collect kernel files
    include("${KERNEL_DIR}/file_list.cmake")

    if (NOT DEFINED SCPU_FILE_LIST)
        set(CURR_FILE_LIST ${FILE_LIST})
    else()
        set(CURR_FILE_LIST ${SCPU_FILE_LIST})

        if (BUILD_KCPU_FILES)
            # add FILE_LIST
            set(CURR_FILE_LIST ${CURR_FILE_LIST} ${FILE_LIST})
        endif()
    endif()

    foreach(project_source_path ${CURR_FILE_LIST})

        set(KERNEL_FILE_LIST
            ${KERNEL_FILE_LIST}
            "${KERNEL_DIR}/${project_source_path}"
        )

    endforeach()

    include("${SCRIPT_DIR}/unity_build.cmake")

    unity_build(
        ${PROJECT_NAME}_SCPU
        "${KERNEL_FILE_LIST}"
    )

endif()


#################################
# add project source files
#################################
# get sources from directory
set(PROJECT_SOURCE_DIRS
    ${ABS_USER_DEVICE_DIRS}
)

if( NOT USE_UNITY_BUILD )
    set(PROJECT_SOURCE_DIRS
        "${KERNEL_DIR}"
        ${PROJECT_SOURCE_DIRS}
    )
endif()

if (BUILD_KCPU_FILES)
    # add user directories
    list(APPEND
        PROJECT_SOURCE_DIRS
        ${ABS_USER_DIRS}
    )
endif()

# add files
foreach(project_source_dir ${PROJECT_SOURCE_DIRS})

    unset(FILE_LIST)
    unset(SCPU_FILE_LIST)

    include("${project_source_dir}/file_list.cmake")

    if (NOT DEFINED SCPU_FILE_LIST)
        set(CURR_FILE_LIST ${FILE_LIST})
    else()
        set(CURR_FILE_LIST ${SCPU_FILE_LIST})

        if (BUILD_KCPU_FILES)
            # add FILE_LIST
            set(CURR_FILE_LIST ${CURR_FILE_LIST} ${FILE_LIST})
        endif()
    endif()

    foreach(project_source_path ${CURR_FILE_LIST})

        file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${project_source_dir}/${project_source_path}" )

        if(${project_source_path} MATCHES ".*\.a$")
            # lib file
            set(PROJECT_LIBS
                ${PROJECT_LIBS}
                "${CMAKE_CURRENT_SOURCE_DIR}/${relative_path}"
            )
        else()
            # source file
            set(PROJECT_SOURCES
                ${PROJECT_SOURCES}
                "${CMAKE_CURRENT_SOURCE_DIR}/${relative_path}"
            )
        endif()

    endforeach()

endforeach()

target_sources(${PROJECT_NAME}_SCPU PUBLIC
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME}_SCPU
    ${PROJECT_LIBS}
    "gcc"
    "c"
    "m"
    "nosys"
)

# set compile flags by file
get_target_property(PROJECT_SOURCES ${PROJECT_NAME}_SCPU SOURCES)

foreach(source_file ${PROJECT_SOURCES})

    set(COMPILE_FLAGS "")

    if(NOT ASM_SRC_OUTPUT)
        get_filename_component(basename ${source_file} NAME)

        # generate assembly dump
        set(COMPILE_FLAGS "${COMPILE_FLAGS} -Wa,-adln=dump/${basename}.S -Wa,--listing-rhs-width=1000")
    endif()

    # update compile flag based on language
    get_source_file_property(_location ${source_file} LOCATION)
    get_source_file_property(language ${source_file} LANGUAGE)

    if(${language} STREQUAL "C")
        set(COMPILE_FLAGS "${COMPILE_FLAGS} ${C_FLAGS}")
    endif()

    if(${language} STREQUAL "CXX")
        set(COMPILE_FLAGS "${COMPILE_FLAGS} ${CXX_FLAGS}")
    endif()

    if(${language} STREQUAL "ASM")
        set(COMPILE_FLAGS "${COMPILE_FLAGS} ${ASM_FLAGS}")
    endif()

    set_source_files_properties(${source_file}
        PROPERTIES
            COMPILE_FLAGS ${COMPILE_FLAGS}
    )
endforeach()
