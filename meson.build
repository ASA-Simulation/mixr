project('mixr', 'cpp',
    version: '1.0.5',
    license: 'LGPL-3.0',
    default_options : [
        'default_library=shared',
        'c_std=c11',
        'cpp_std=c++11',
        'c_args=-fPIC',
        'cpp_args=-fPIC',
    ],
)

add_project_arguments('-fpermissive', language : 'cpp')

#
# Linker flags for mostly static builds
#

static_flags = [
    '-static-libstdc++',   # embed libstdc++.a
    '-static-libgcc',      # embed libgcc.a
]

#
# Dependencies: system and 3rd party
#

pkg = import('pkgconfig')

thread_dep = dependency('threads')

protobuf_dep = dependency('protobuf')
jsbsim_dep = dependency('jsbsim')
openrti_dep = dependency('openrti')
zlib_dep = dependency('zlib')

protoc = '@0@/bin/protoc'.format(protobuf_dep.get_variable('prefix'))

public_headers = include_directories('include')

#
# Libraries
#

subdir('./src')

#
# Installation
#

pkg.generate(
    description : 'A fork of MIXR focused on meson/conan integration.',
    filebase : 'mixr',
    libraries : [
        mixr_base,
        mixr_interop_common,
        mixr_interop_dis,
        mixr_linearsystem,
        mixr_linkage,
        mixr_models,
        mixr_recorder,
        mixr_simulation,
        mixr_terrain,
    ],
    name : 'mixr',
)

install_subdir('include/mixr', install_dir : 'include')
