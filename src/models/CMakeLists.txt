# Target: libmixr_models.a
add_library(mixr_models STATIC)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_sources(mixr_models
    PRIVATE
        ${src_files}
)

target_include_directories(mixr_models
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_models
    PUBLIC
        mixr_base
    PRIVATE
        jsbsim::jsbsim
)
