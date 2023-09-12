# Target: libMixrSimulation[d].so
add_library(MixrSimulation SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_sources(MixrSimulation
    PRIVATE
        ${src_files}
)

target_include_directories(MixrSimulation
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MixrSimulation
    PUBLIC
        MixrBase
)
