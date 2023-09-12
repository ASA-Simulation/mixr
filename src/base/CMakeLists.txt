# Target: libMixrBase[d].so
add_library(MixrBase SHARED)

file(GLOB_RECURSE src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/**.cpp
)

# TODO: why this file shouldn't be compiled?
list(REMOVE_ITEM src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/osg/Matrix_implementation.cpp
)

# Platform specific
if(WIN32)
    # Assuming we're on Windows

    list(FILTER src_files EXCLUDE REGEX
        ".*_linux.cpp$"
    )

    list(FILTER src_files EXCLUDE REGEX
        ".*_mingw.cpp$"
    )
else()
    # Assuming we're on Linux

    list(FILTER src_files EXCLUDE REGEX
        ".*_mingw.cpp$"
    )

    list(FILTER src_files EXCLUDE REGEX
        ".*_msvc.cpp$"
    )
endif()

target_sources(MixrBase
    PRIVATE
        ${src_files}
)

target_include_directories(MixrBase
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
