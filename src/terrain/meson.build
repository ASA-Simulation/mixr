source_files = [
    './DataFile.cpp',
    './factory.cpp',
    './QuadMap.cpp',
    './Terrain.cpp',
    './srtm/SrtmHgtFile.cpp',
    './ded/DedFile.cpp',
    './dted/DtedFile.cpp',
]

mixr_terrain = library(
    'mixr_terrain',
    source_files,
    include_directories: public_headers,
    dependencies: [
        mixr_base_dep
    ],
    link_args : [
        static_flags
    ],
    install : true,
)

mixr_terrain_dep = declare_dependency(
    link_with : mixr_terrain
)

pkg.generate(mixr_terrain, name : 'mixr-terrain')
