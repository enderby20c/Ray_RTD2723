# generate unity build file
# Args:
#   proname_name: project to be checked
#   file_list:
function (unity_build project_name file_list)

    # add unified target to provide compile commands for original files
    add_library(${project_name}_unified OBJECT EXCLUDE_FROM_ALL)

    get_target_property(project_include_directories ${project_name} INCLUDE_DIRECTORIES)
    get_target_property(project_compile_definitions ${project_name} COMPILE_DEFINITIONS)
    get_target_property(project_compile_options ${project_name} COMPILE_OPTIONS)

    target_include_directories(${project_name}_unified PUBLIC
        ${project_include_directories}
    )

    target_compile_definitions(${project_name}_unified PUBLIC
        ${project_compile_definitions}
    )

    target_compile_options(${project_name}_unified PUBLIC
        ${project_compile_options}
    )

    set(UNITY_BUILD_SKIP_LIST
        "UserCommonColor.c"
        "UserCommonModeSearch.c"
        "ScalerDDomain.c"
    )

    # remove duplicate files
    list(REMOVE_DUPLICATES file_list)

    # add files
    foreach(project_source_path ${file_list})

        file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${project_source_path}" )

        get_filename_component(basename ${relative_path} NAME)

        if(${project_source_path} MATCHES ".*\.c$")

            # C source file
            if((${project_source_path} MATCHES ".*Common/.*$") OR
               (${basename} IN_LIST UNITY_BUILD_SKIP_LIST))
                set(PROJECT_SOURCES
                    ${PROJECT_SOURCES}
                    "${CMAKE_CURRENT_SOURCE_DIR}/${relative_path}"
                )
            else()

                set(UNITY_PROJECT_SOURCES
                    ${UNITY_PROJECT_SOURCES}
                    "#include \"${relative_path}\""
                )

                # add to unity target
                target_sources(${project_name}_unified PUBLIC
                    "${CMAKE_CURRENT_SOURCE_DIR}/${relative_path}"
                )
            endif()

        elseif(${project_source_path} MATCHES ".*\.a$")
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

    # separate system files
    target_unity_sources_with_filter(${project_name}
        "unity_system"
        "${UNITY_PROJECT_SOURCES}"
        UNITY_PROJECT_SOURCES
        ".*System.*"
    )

    # separate user common files
    target_unity_sources_with_filter(${project_name}
        "unity_user_common"
        "${UNITY_PROJECT_SOURCES}"
        UNITY_PROJECT_SOURCES
        ".*UserCommonFunction.*"
    )

    # separate DP aux files
    target_unity_sources_with_filter(${project_name}
        "unity_scaler_dp_aux"
        "${UNITY_PROJECT_SOURCES}"
        UNITY_PROJECT_SOURCES
        ".*Dp(Aux|Audio|Hdcp).*"
    )

    # separate DP files
    target_unity_sources_with_filter(${project_name}
        "unity_scaler_dp"
        "${UNITY_PROJECT_SOURCES}"
        UNITY_PROJECT_SOURCES
        ".*Dp.*"
    )

    # separate TMDS files
    target_unity_sources_with_filter(${project_name}
        "unity_scaler_tmds"
        "${UNITY_PROJECT_SOURCES}"
        UNITY_PROJECT_SOURCES
        ".*(Tmds|Hdmi).*"
    )

    # separate usb files
    target_unity_sources_with_filter(${project_name}
        "unity_scaler_usb"
        "${UNITY_PROJECT_SOURCES}"
        UNITY_PROJECT_SOURCES
        ".*(Usb|GDI|TypeC).*"
    )

    # separate color files
    target_unity_sources_with_filter(${project_name}
        "unity_scaler_color"
        "${UNITY_PROJECT_SOURCES}"
        UNITY_PROJECT_SOURCES
        ".*Color.*"
    )

    # separate cpu/misc files
    target_unity_sources_with_filter(${project_name}
        "unity_scaler_cpu"
        "${UNITY_PROJECT_SOURCES}"
        UNITY_PROJECT_SOURCES
        ".*(Mcu|Cpu|Global|Osd|Reg|Scpu|Wdt|Timer).*"
    )

    # separate scaler base files
    target_unity_sources_with_filter(${project_name}
        "unity_scaler_base"
        "${UNITY_PROJECT_SOURCES}"
        UNITY_PROJECT_SOURCES
        ".*_Series_Scaler.*"
    )

    # collect remaining files
    target_unity_sources(${project_name}
        "unity_other"
        "${UNITY_PROJECT_SOURCES}"
    )

    # return variables
    set(PROJECT_LIBS ${PROJECT_LIBS} PARENT_SCOPE)
    set(PROJECT_SOURCES ${PROJECT_SOURCES} PARENT_SCOPE)

endfunction()


# generate unity build file with filter
# Args:
#   project_name:
#   unity_file_name:
#   content_list: list to be filtered
#   exclude_list_name: return parameter name
#   filter: regex
function (target_unity_sources_with_filter project_name unity_file_name content_list exclude_list_name filter )

    set(include_list ${content_list})
    set(exclude_list ${content_list})

    list(FILTER include_list INCLUDE REGEX "${filter}")
    list(FILTER exclude_list EXCLUDE REGEX "${filter}")

    set(${exclude_list_name} "${exclude_list}" PARENT_SCOPE)

    set(include_normal_list "")
    set(include_int_list "")

    # separate INT functions
    foreach(source_path ${include_list})

        get_filename_component(basename ${source_path} NAME)

        if(${basename} MATCHES ".*INT.*")
            list(APPEND include_int_list ${source_path})
        else()
            list(APPEND include_normal_list ${source_path})
        endif()

    endforeach()

    target_unity_sources(${project_name}
        "${unity_file_name}"
        "${include_normal_list}"
    )

    target_unity_sources(${project_name}
        "${unity_file_name}_INT"
        "${include_int_list}"
    )

endfunction()


# generate unity build file
# Args:
#   project_name:
#   unity_file_name:
#   content_list:
function (target_unity_sources project_name unity_file_name content_list)

    set(UNITY_OUTPUT_FILE
        "${CMAKE_OUTPUT_DIR}/unity/${unity_file_name}.c"
    )

    string(JOIN "\n" UNITY_CONTENT
        ${content_list}
    )

    # skip empty content
    if ( "${UNITY_CONTENT}" STREQUAL "" )
        return()
    endif()

    if (NOT EXISTS "${UNITY_OUTPUT_FILE}")

        file(WRITE "${UNITY_OUTPUT_FILE}" "${UNITY_CONTENT}\n")

    else()
        # compare old unity output and update only if changed
        file(READ "${UNITY_OUTPUT_FILE}" OLD_UNITY_CONTENT)

        string(COMPARE NOTEQUAL
            "${UNITY_CONTENT}\n"
            "${OLD_UNITY_CONTENT}"
            UNITY_OUTPUT_UPDATED
        )

        if (UNITY_OUTPUT_UPDATED)
            file(WRITE "${UNITY_OUTPUT_FILE}" "${UNITY_CONTENT}\n")
        endif()

    endif()

    # add to target
    target_sources(${project_name} PUBLIC
        "${UNITY_OUTPUT_FILE}"
    )

endfunction()
