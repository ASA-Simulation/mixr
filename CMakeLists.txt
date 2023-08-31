# CMakeLists.txt
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(mixr
    VERSION 0.1.0
    LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_DEBUG_POSTFIX "d")

#
# External dependencies
#

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG "yes" CACHE BOOL "")

find_package(Protobuf CONFIG REQUIRED)

find_package(JSBSim   CONFIG REQUIRED)
find_package(OpenRTI  CONFIG REQUIRED)

#
# MIXR project
#

add_subdirectory(src)

set(ALL_TARGETS
    mixr_base
    mixr_interop_dis
    mixr_interop_hla
    mixr_interop
    mixr_interop_rprfom
    mixr_linearsystem
    mixr_linkage
    mixr_models
    mixr_recorder
    mixr_simulation
    mixr_terrain
)

#
# Installation
#

# Building an exportable

install(
    TARGETS     ${ALL_TARGETS}
    EXPORT      MIXRTargets

    LIBRARY     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME     DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Installing headers

install(
    FILES
        ${CMAKE_BINARY_DIR}/src/recorder/proto/DataRecord.pb.h
        ${CMAKE_SOURCE_DIR}/src/recorder/proto/DataRecord.proto
    DESTINATION include/mixr/recorder
)

install(
    FILES
        ${CMAKE_BINARY_DIR}/src/recorder/proto/DataRecord.pb.h
        ${CMAKE_SOURCE_DIR}/src/recorder/proto/DataRecord.proto
    DESTINATION include
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/mixr
    DESTINATION include
)
