# Target: libMixrTerrain[d].so
add_library(MixrTerrain SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/**.cpp)

target_sources(MixrTerrain
    PRIVATE
        ${src_files}
)

target_include_directories(MixrTerrain
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MixrTerrain
    PUBLIC
        MixrBase
)
