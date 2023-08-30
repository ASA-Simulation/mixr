# Target: libmixr_recorder_proto.a

add_subdirectory(proto)

# Target: libmixr_recorder.a
add_library(mixr_recorder STATIC)

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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/proto>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_recorder
    PUBLIC
        mixr_base
        mixr_recorder_proto
    PRIVATE
        protobuf::libprotobuf
)
