#################################
# build script for 32-bit second CPU(SCPU) boot
#################################
set(BUILD_TEMPLATE "build_SCPU_boot")

if( NO_LINK )
    add_library(${PROJECT_NAME}_SCPU_BOOT OBJECT)
else()
    add_executable(${PROJECT_NAME}_SCPU_BOOT)
endif()

add_custom_target(${PROJECT_NAME} ALL
    DEPENDS
        ${PROJECT_NAME}_SCPU_BOOT
)


#################################
# include path settings for .h files
#################################
target_include_directories(${PROJECT_NAME}_SCPU_BOOT PUBLIC
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
target_compile_definitions(${PROJECT_NAME}_SCPU_BOOT PUBLIC
    "_CPU32_IP=_CPU32_IP_${CPU_TYPE}"
    "_HW_CPU32_IS_BOOT_CPU=_FALSE"

    # add user-defined C #define
    ${C_DEFINE}

    # add generated C #define
    "REENTRANT_SYSCALLS_PROVIDED"
    "USE_HAL_DRIVER"

    "CPU32_BOOTLOADER"
)

if(USE_ASSERT)
    target_compile_definitions(${PROJECT_NAME}_SCPU_BOOT PUBLIC
        "USE_FULL_ASSERT"
    )
endif()

# add resource flags
if(ABS_USER_EMBEDDED_RESOURCE_DIRS)
    target_compile_definitions(${PROJECT_NAME}_SCPU_BOOT PUBLIC
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
target_compile_options(${PROJECT_NAME}_SCPU_BOOT PUBLIC
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
# custom settings
#################################
# add custom optimization level
if(NOT ${OPT_LEVEL} STREQUAL "-Odefault")
    target_compile_options(${PROJECT_NAME}_SCPU_BOOT PUBLIC
        "${OPT_LEVEL}"
    )
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME}_SCPU_BOOT PUBLIC
        "DEBUG"
        "OS_USE_TRACE_SEMIHOSTING_DEBUG"
    )

    target_compile_options(${PROJECT_NAME}_SCPU_BOOT PUBLIC
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
        "${OUTPUT_DIR}/COMMON_FILES/${PROJECT_NAME}_SCPU_BOOT.ld"
    )
    set(PROJECT_MAP_FILE
        "${OUTPUT_DIR}/COMMON_FILES/${PROJECT_NAME}_SCPU_BOOT.map"
    )

    set(PROJECT_LOCATION_FILE
        "${OUTPUT_DIR}/COMMON_FILES/${PROJECT_NAME}_SCPU_BOOT.ld.syms"
    )

    string(JOIN " " LD_FLAGS
        ${GLOBAL_LDFLAGS}
        "-Wl,--sort-section=name"
        "-Wl,-T\"${PROJECT_LINK_FILE}\""
        "-Wl,-Map,\"${PROJECT_MAP_FILE}\""
        "-Wl,-R,\"${PROJECT_LOCATION_FILE}\""
    )

    set_target_properties(${PROJECT_NAME}_SCPU_BOOT PROPERTIES
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
        ./build_actions_SCPU_boot.sh pre_build
    DEPENDS
        "${CMAKE_OUTPUT_DIR}/cpp_cmd.sh"
    COMMENT
        "run pre-build"
)

if( NOT NO_LINK )
    add_custom_command(TARGET ${PROJECT_NAME}_SCPU_BOOT
        PRE_LINK
            COMMAND
                ./build_actions_SCPU_boot.sh pre_link
            COMMENT
                "run pre-link"
    )

    add_custom_command(TARGET ${PROJECT_NAME}_SCPU_BOOT
        POST_BUILD
            COMMAND
                ./build_actions_SCPU_boot.sh post_build
            COMMENT
                "run post-build"
    )
endif()

add_custom_target("clean_all"
        ./build_actions_SCPU_boot.sh clean_all
    COMMENT
        "run clean"
)


#################################
# custom compiler command settings
#################################
# CPP script
add_custom_command(
    OUTPUT
        "${CMAKE_OUTPUT_DIR}/cpp_cmd.sh"
    COMMAND
        echo ${CPP} "-D$<JOIN:$<TARGET_PROPERTY:${PROJECT_NAME}_SCPU_BOOT,COMPILE_DEFINITIONS>, -D>" "-I\"$<JOIN:$<TARGET_PROPERTY:${PROJECT_NAME}_SCPU_BOOT,INCLUDE_DIRECTORIES>,\" -I\">\"" "\"\$\$\"*" > "${CMAKE_OUTPUT_DIR}/cpp_cmd.sh"
    COMMAND
        chmod +x "${CMAKE_OUTPUT_DIR}/cpp_cmd.sh"
)


#################################
# generate templates
#################################
set(TEMPLATE_FILES
    "build_actions/build_actions_SCPU_boot.sh"
    "build_actions/build_actions_post_complier.sh"
    "build_actions/build_actions_data_section_rename.sh"
    "build_actions/${SCALER_NAME}_build_actions.sh"
    "wrapper/auto_link32_wrapper.sh"
    "helper.sh"

    # options
    "build_options_rename_ddr_data"
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
# add project source files
#################################
# get sources from directory
set(PROJECT_SOURCE_DIRS
    "${KERNEL_DIR}"
    ${ABS_USER_EMBEDDED_RESOURCE_DIRS}
)

# add files
foreach(project_source_dir ${PROJECT_SOURCE_DIRS})

    include("${project_source_dir}/file_list.cmake")

    foreach(project_source_path ${FILE_LIST})

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

target_sources(${PROJECT_NAME}_SCPU_BOOT PUBLIC
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME}_SCPU_BOOT
    ${PROJECT_LIBS}
)

# set compile flags by file
get_target_property(PROJECT_SOURCES ${PROJECT_NAME}_SCPU_BOOT SOURCES)

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
