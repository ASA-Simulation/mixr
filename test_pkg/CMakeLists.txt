cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG "yes" CACHE BOOL "")

find_package(mixr CONFIG REQUIRED
    COMPONENTS
        base
)

add_executable(example src/example.cpp)
target_link_libraries(example mixr::base)
