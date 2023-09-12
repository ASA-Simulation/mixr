# Target: libmixr_linearsystem[d].so
add_library(mixr_linearsystem SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_sources(mixr_linearsystem
    PRIVATE
        ${src_files}
)

target_include_directories(mixr_linearsystem
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_linearsystem
    PUBLIC
        mixr_base
)
