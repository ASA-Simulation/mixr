# Target: libMixrInterop[d].so
add_library(MixrInterop SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp)

target_sources(MixrInterop
    PRIVATE
        ${src_files}
)

target_include_directories(MixrInterop
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MixrInterop
    PUBLIC
        MixrBase
)



# Target: libMixrInteropDis[d].so
add_library(MixrInteropDis SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/dis/*.cpp)

target_sources(MixrInteropDis
    PRIVATE
        ${src_files}
)

target_include_directories(MixrInteropDis
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MixrInteropDis
    PUBLIC
        MixrBase
)



# Target: libMixrInteropHla[d].so
add_library(MixrInteropHla SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/hla/*.cpp)

target_sources(MixrInteropHla
    PRIVATE
    ${src_files}
)

target_include_directories(MixrInteropHla
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MixrInteropHla
    PUBLIC
        MixrBase
    PRIVATE
        openrti::openrti
)



# Target: libMixrInteropRprfom[d].so
add_library(MixrInteropRprfom SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/rprfom/*.cpp)

target_sources(MixrInteropRprfom
    PRIVATE
        ${src_files}
)

target_include_directories(MixrInteropRprfom
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INC_INSTALL_DIR}>
)

target_link_libraries(MixrInteropRprfom
    PUBLIC
        MixrBase
    PRIVATE
        openrti::openrti
)
