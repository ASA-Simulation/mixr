# Target: libmixr_recorder_proto.a

set(PROTO_FILES
    DataRecord.proto
)

add_library(mixr_recorder_proto
    ${PROTO_FILES}
)

target_link_libraries(mixr_recorder_proto
    PUBLIC
        protobuf::libprotobuf
)

target_include_directories(mixr_recorder_proto
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/>
)

# compile the message types
protobuf_generate(TARGET mixr_recorder_proto LANGUAGE cpp)
