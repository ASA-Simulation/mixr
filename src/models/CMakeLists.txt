# Target: libMixrModels[d].so
add_library(MixrModels SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_sources(MixrModels
    PRIVATE
        ${src_files}
)

target_include_directories(MixrModels
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MixrModels
    PUBLIC
        MixrBase
    PRIVATE
        jsbsim::jsbsim
)
