# components/Apps/CMakeLists.txt

# Specify the path to the Pulse compiler executable
set(PULSE_COMPILER_EXEC ${CMAKE_BINARY_DIR}/components/Pulse/pulse-compiler)

if(NOT EXISTS ${PULSE_COMPILER_EXEC})
    message(FATAL_ERROR "Pulse compiler not found at ${PULSE_COMPILER_EXEC}. Please build the Pulse compiler first.")
endif()

# Function to compile a .pls file into an executable
function(add_pls_app app_name pls_file)
    add_custom_command(
        OUTPUT ${app_name}.exe
        COMMAND ${PULSE_COMPILER_EXEC} ${pls_file} -o ${app_name}.exe
        DEPENDS ${pls_file} ${PULSE_COMPILER_EXEC}
        COMMENT "Compiling ${pls_file} into ${app_name}.exe"
    )

    add_custom_target(${app_name} ALL DEPENDS ${app_name}.exe)

    # Optionally, install the executable
    install(FILES ${app_name}.exe DESTINATION bin/${app_name})
endfunction()

# Iterate over each app directory and compile the .pls file
file(GLOB APP_DIRS LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(APP_DIR ${APP_DIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${APP_DIR})
        # Assume the .pls file has the same name as the directory
        set(PLS_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${APP_DIR}/${APP_DIR}.pls)
        if(EXISTS ${PLS_FILE})
            add_pls_app(${APP_DIR} ${PLS_FILE})
        else()
            message(WARNING "No .pls file found for app: ${APP_DIR}")
        endif()
    endif()
endforeach()
