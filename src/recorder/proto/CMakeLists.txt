# Target: libmixr_recorder_proto[d].so
file(GLOB_RECURSE proto_files
    ${CMAKE_CURRENT_SOURCE_DIR}/**.proto
)

add_library(mixr_recorder_proto SHARED
    ${proto_files}
)

protobuf_generate(TARGET mixr_recorder_proto LANGUAGE cpp)

target_link_libraries(mixr_recorder_proto
    PUBLIC
        protobuf::libprotobuf
)

target_include_directories(mixr_recorder
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
