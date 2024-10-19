# check if condition is TRUE for specified projcect configuration
# Args:
#   proname_name: project to be checked
#   condition: condition string to be checked by pre-processor
#   result: test result will be store in this variable
#   log: test log
function (test_project_condition project_name condition result log)

    set(TEST_CONDITION
        "${condition}"
    )

    configure_file(
        "${SCRIPT_DIR}/template/test_compile.c.in"
        "${CMAKE_OUTPUT_DIR}/try_compile.c"
        @ONLY
    )

    get_target_property(TRY_INCLUDE_DIRECTORIES ${project_name} INCLUDE_DIRECTORIES)
    get_target_property(TRY_COMPILE_DEFINITIONS ${project_name} COMPILE_DEFINITIONS)

    foreach(compile_definition ${TRY_COMPILE_DEFINITIONS})
        set(TRY_COMPILE_DEFINITIONS_STR
            "${TRY_COMPILE_DEFINITIONS_STR}"
            "-D${compile_definition}"
        )
    endforeach()

    list(POP_FRONT TRY_COMPILE_DEFINITIONS_STR)

    try_compile(try_result
        "${CMAKE_OUTPUT_DIR}/try"

        SOURCES
            "${CMAKE_OUTPUT_DIR}/try_compile.c"
        CMAKE_FLAGS
            "-DINCLUDE_DIRECTORIES=${TRY_INCLUDE_DIRECTORIES}"
        COMPILE_DEFINITIONS
            ${TRY_COMPILE_DEFINITIONS_STR}
        C_STANDARD
            "11"
        OUTPUT_VARIABLE
            try_log
    )

    SET(${result} ${try_result} PARENT_SCOPE)
    SET(${log} ${try_log} PARENT_SCOPE)

endfunction()


# test if try-compile is working properly
# Args:
#   proname_name: project to be checked
function (test_condition_check project_name)

    test_project_condition(
        ${project_name}
        "_ON"
        try_result
        try_log
    )

    if (NOT try_result)
        message("FATAL_ERROR" ${try_log})
    endif()

endfunction()


# check if condition is TRUE for specified projcect configuration
# Args:
#   proname_name: project to be checked
#   condition: condition string to be checked by pre-processor
#   result: test result will be store in this variable
function (test_condition project_name condition result)

    test_project_condition(
        ${project_name}
        ${condition}
        try_result
        try_log
    )

    SET(${result} ${try_result} PARENT_SCOPE)

    message(STATUS "Try compile result is ${try_result}: '${condition}'")

endfunction()
