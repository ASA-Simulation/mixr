# Target: libMixrLinkage[d].so
add_library(MixrLinkage SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Platform specific
if(WIN32)
    # Assuming we're on Windows

    list(FILTER src_files EXCLUDE REGEX
        ".*_linux.cpp$"
    )
else()
    # Assuming we're on Linux

    list(FILTER src_files EXCLUDE REGEX
        ".*_msvc.cpp$"
    )
endif()

target_sources(MixrLinkage
    PRIVATE
        ${src_files}
)

target_include_directories(MixrLinkage
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MixrLinkage
    PUBLIC
        MixrBase
)
