# fmt
CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG e69e5f977d458f2650bb346dadf2ad30c5320281
)

if(fmt_ADDED)
        set_target_properties(fmt PROPERTIES CXX_STANDARD 23)
        set_target_properties(fmt-header-only PROPERTIES CXX_STANDARD 23)
endif()
