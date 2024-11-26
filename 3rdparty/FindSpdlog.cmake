# spdlog
CPMAddPackage(
        NAME spdlog
        GITHUB_REPOSITORY gabime/spdlog
        GIT_TAG 8e5613379f5140fefb0b60412fbf1f5406e7c7f8
        OPTIONS
        "SPDLOG_BUILD_EXAMPLE OFF"
        "SPDLOG_FMT_EXTERNAL ON"
        "SPDLOG_FMT_EXTERNAL_HO OFF"
        "SPDLOG_DISABLE_DEFAULT_LOGGER ON"
        "SPDLOG_NO_EXCEPTIONS ON"
)

if(spdlog_ADDED)
        set_target_properties(spdlog PROPERTIES CXX_STANDARD 20)
endif()
