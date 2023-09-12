# Target: libMixrRecorderProto[d].so
file(GLOB_RECURSE proto_files
    ${CMAKE_CURRENT_SOURCE_DIR}/**.proto
)

add_library(MixrRecorderProto SHARED
    ${proto_files}
)

protobuf_generate(TARGET MixrRecorderProto LANGUAGE cpp)

target_link_libraries(MixrRecorderProto
    PUBLIC
        protobuf::libprotobuf
)

target_include_directories(MixrRecorderProto
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
