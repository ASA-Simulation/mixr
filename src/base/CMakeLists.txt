# Target: libmixr_base[d].so
add_library(mixr_base SHARED)

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

target_sources(mixr_base
    PRIVATE
        ${src_files}
)

target_include_directories(mixr_base
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
