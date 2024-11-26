# Pre-commit hooks
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/.git/hooks/pre-commit)
    message(STATUS "Installing pre-commit hooks")

    if(POLICY CMP0094) # https://cmake.org/cmake/help/latest/policy/CMP0094.html
        cmake_policy(SET CMP0094 NEW) # FindPython should return the first matching Python
    endif()

    # needed on GitHub Actions CI: actions/setup-python does not touch registry/frameworks on Windows/macOS this mirrors
    # PythonInterp behavior which did not consult registry/frameworks first
    if(NOT DEFINED Python_FIND_REGISTRY)
        set(Python_FIND_REGISTRY "LAST")
    endif()

    if(NOT DEFINED Python_FIND_FRAMEWORK)
        set(Python_FIND_FRAMEWORK "LAST")
    endif()

    find_package(Python REQUIRED COMPONENTS Interpreter)
    message(STATUS "Python executable: ${Python_EXECUTABLE}")

    set(VENV_PATH ${PROJECT_SOURCE_DIR}/.venv)

    if(NOT EXISTS ${VENV_PATH})
        execute_process(COMMAND ${Python_EXECUTABLE} -m venv ${VENV_PATH} RESULT_VARIABLE VENV_CREATION_RESULT)

        if(NOT VENV_CREATION_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to create Python virtual environment.")
        endif()

        # 根据操作系统设置激活脚本路径
        if(WIN32)
            set(ACTIVATE_SCRIPT "${VENV_DIR}/Scripts/activate")
            set(PIP_EXECUTABLE "${VENV_DIR}/Scripts/pip")
        else()
            set(ACTIVATE_SCRIPT "${VENV_DIR}/bin/activate")
            set(PIP_EXECUTABLE "${VENV_DIR}/bin/pip")
        endif()
    endif()

    set(HOOK_INSTALL_PACKAGE pre-commit)

    # Find clang-format executable
    find_program(CLANG_FORMAT_EXECUTABLE clang-format)

    if(CLANG_FORMAT_EXECUTABLE)
        message(STATUS "clang-format executable: ${CLANG_FORMAT_EXECUTABLE}")
    else()
        message(WARNING "clang-format executable not found, need install")
        set(HOOK_INSTALL_PACKAGE ${HOOK_INSTALL_PACKAGE} clang-format)
    endif()

    execute_process(COMMAND ${Python_EXECUTABLE} -m pip install ${HOOK_INSTALL_PACKAGE}
        RESULT_VARIABLE PIP_INSTALL_RESULT
    )

    if(NOT PIP_INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to install pre-commit hooks.")
    endif()

    execute_process(COMMAND pre-commit install WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        RESULT_VARIABLE PRE_COMMIT_INSTALL_RESULT
    )

    if(NOT PRE_COMMIT_INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to install pre-commit hooks.")
    endif()
endif()
