# Target: libmixr_recorder[d].so
add_library(mixr_recorder SHARED)

add_subdirectory(proto)

file(GLOB_RECURSE src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

target_sources(mixr_recorder
    PRIVATE
        ${src_files}
)

target_include_directories(mixr_recorder
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/proto>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_recorder
    PUBLIC
        mixr_base
        mixr_recorder_proto
        protobuf::libprotobuf
)
