# Target: libMixrLinearSystem[d].so
add_library(MixrLinearSystem SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_sources(MixrLinearSystem
    PRIVATE
        ${src_files}
)

target_include_directories(MixrLinearSystem
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MixrLinearSystem
    PUBLIC
        MixrBase
)
