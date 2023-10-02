project('mixr', 'cpp',
    default_options : [
        'c_std=c11',
        'cpp_std=c++11',
    ],
)

add_project_arguments('-fpermissive', language : 'cpp')

pkg = import('pkgconfig')

thread_dep = dependency('threads')

protobuf_dep = dependency('protobuf')
jsbsim_dep = dependency('jsbsim')
openrti_dep = dependency('openrti')
zlib_dep = dependency('zlib')

public_headers = include_directories('include')

subdir('./src')

# Installation

meson.add_install_script('./scripts/install.sh')

mixr_libs = [
    mixr_base,
    mixr_interop_common,
    mixr_interop_dis,
    mixr_linearsystem,
    mixr_linkage,
    mixr_models,
    mixr_recorder,
    mixr_recorder_proto,
    mixr_simulation,
    mixr_terrain,
]

install_subdir('include/mixr', install_dir : 'include')

pkg.generate(
    libraries : mixr_libs,
    version : '1.0.5',
    name : 'mixr',
    filebase: 'mixr',
    description: 'A fork of MIXR focused on meson/conan integration.',
)