# Target: libmixr_recorder.a
add_library(mixr_simulation STATIC)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_sources(mixr_simulation
    PRIVATE
        ${src_files}
)

target_include_directories(mixr_simulation
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_simulation
    PUBLIC
        mixr_base
)
