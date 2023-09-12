# Target: libmixr_recorder[d].so
add_library(mixr_terrain SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/**.cpp)

target_sources(mixr_terrain
    PRIVATE
        ${src_files}
)

target_include_directories(mixr_terrain
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_terrain
    PUBLIC
        mixr_base
)
