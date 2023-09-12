# Target: libmixr_interop[d].so
add_library(mixr_interop SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp)

target_sources(mixr_interop
    PRIVATE
        ${src_files}
)

target_include_directories(mixr_interop
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_interop
    PUBLIC
        mixr_base
)



# Target: libmixr_interop_dis[d].so
add_library(mixr_interop_dis SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/dis/*.cpp)

target_sources(mixr_interop_dis
    PRIVATE
        ${src_files}
)

target_include_directories(mixr_interop_dis
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_interop_dis
    PUBLIC
        mixr_base
)



# Target: libmixr_interop_hla[d].so
add_library(mixr_interop_hla SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/hla/*.cpp)

target_sources(mixr_interop_hla
    PRIVATE
    ${src_files}
)

target_include_directories(mixr_interop_hla
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(mixr_interop_hla
    PUBLIC
        mixr_base
    PRIVATE
        openrti::openrti
)



# Target: libmixr_interop_rprfom[d].so
add_library(mixr_interop_rprfom SHARED)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/rprfom/*.cpp)

target_sources(mixr_interop_rprfom
    PRIVATE
        ${src_files}
)

target_include_directories(mixr_interop_rprfom
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INC_INSTALL_DIR}>
)

target_link_libraries(mixr_interop_rprfom
    PUBLIC
        mixr_base
    PRIVATE
        openrti::openrti
)
