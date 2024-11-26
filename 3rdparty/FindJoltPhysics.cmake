CPMAddPackage(
        NAME JoltPhysics
        GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
        GIT_TAG "d6e015372b08f28c3c62e9aaab9a5cb2af667e54"
        SOURCE_SUBDIR "Build"
)

set_target_properties(Jolt PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
