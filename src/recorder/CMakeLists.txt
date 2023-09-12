# Target: libMixrRecorder[d].so
add_library(MixrRecorder SHARED)

add_subdirectory(proto)

file(GLOB_RECURSE src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

target_sources(MixrRecorder
    PRIVATE
        ${src_files}
)

target_include_directories(MixrRecorder
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/proto>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MixrRecorder
    PUBLIC
        MixrBase
        MixrRecorderProto
        protobuf::libprotobuf
)
