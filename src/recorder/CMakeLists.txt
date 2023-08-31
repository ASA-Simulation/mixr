# Target: libmixr_recorder.a
add_library(mixr_recorder STATIC)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ./proto/DataRecord.proto)

file(GLOB_RECURSE src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

target_sources(mixr_recorder
    PRIVATE
        ${src_files}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
)

target_include_directories(mixr_recorder
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_recorder
    PUBLIC
        mixr_base
        protobuf::libprotobuf
)
