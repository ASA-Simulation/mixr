source_files = [
    './Ntm.cpp',
    './Nib.cpp',
    './NetIO.cpp',
]

mixr_interop_common = library(
    'mixr_interop_common',
    source_files,
    include_directories: [public_headers],
    dependencies: [mixr_base_dep, mixr_simulation_dep, mixr_models_dep, openrti_dep, zlib_dep],
    link_args : [
        static_flags
    ],
    install : true,
)

mixr_interop_common_dep = declare_dependency(
    link_with : mixr_interop_common,
    include_directories : public_headers
)

pkg.generate(mixr_interop_common, name : 'mixr-interop_common')
